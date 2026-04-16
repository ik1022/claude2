# Bare-Metal Firmware — ABOV A31G123 / MindMotion MM32F0162

ARM Cortex-M0 MCU 2종을 지원하는 bare-metal C++ 펌웨어.  
RTOS, CMSIS, 벤더 스타트업 파일 없이 동일한 앱 코드를 CMake 타겟 선택만으로 두 MCU에 빌드할 수 있습니다.

## 지원 MCU

| MCU | Flash | SRAM | 최대 클럭 | Flash 기준 주소 |
|-----|-------|------|-----------|-----------------|
| ABOV A31G123 | 64 KB | 4 KB | 32 MHz | `0x00000000` |
| MindMotion MM32F0162 | 64 KB | 8 KB | 72 MHz | `0x08000000` |

## 필수 도구

- [Node.js](https://nodejs.org/) (xpm 설치에 필요)
- [xPack Project Manager](https://xpack.github.io/xpm/) — `npm install -g xpm`

툴체인(GCC, CMake, Ninja, OpenOCD, QEMU)은 xpm이 자동으로 설치합니다.

```bash
xpm install
```

## 빌드

### xpm (권장)

```bash
# Configure + 빌드
xpm run prepare --config a31g123-release
xpm run build   --config a31g123-release

# 사용 가능한 설정
#   a31g123-debug    a31g123-release
#   mm32f0162-debug  mm32f0162-release

# 전체 빌드 (4개 설정 모두)
xpm run test-all

# 클린
xpm run clean --config a31g123-release
xpm run clean          # 전체 클린
```

### CMake 직접 실행

```bash
cmake -S . -B build/a31g123-debug \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Debug \
      -DTARGET_MCU=A31G123 \
      -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake

cmake --build build/a31g123-debug
```

클럭 주파수 오버라이드:

```bash
cmake ... -DMCU_CLOCK_HZ=16000000
```

### 빌드 결과물

`build/<config>/` 디렉터리에 생성됩니다.

| 파일 | 설명 |
|------|------|
| `firmware` | ELF (디버거용) |
| `firmware.hex` | Intel HEX (플래싱용) |
| `firmware.lst` | 디스어셈블리 |
| `firmware.sym` | 심볼 테이블 |
| `firmware.map` | 링커 맵 |
| `compile_commands.json` | clangd/IDE 언어 서버용 |

## 디렉터리 구조

```
app/            애플리케이션 (MCU-독립, bsp:: + hal:: 만 사용)
bsp/
  board.hpp           인터페이스: bsp::init(), bsp::led::PORT/PIN
  a31g123/board.cpp   보드별 핀 배선 + 초기화
  mm32f0162/board.cpp
core_cm0/       ARM Cortex-M0 공통: 벡터 테이블, 리셋 핸들러, SysTick/NVIC/SCB
hal/            MCU-독립 인터페이스 헤더 (gpio.hpp, clock.hpp, systick.hpp)
mcu/
  a31g123/      실리콘 레지스터 맵(reg/), HAL 구현, IRQ 벡터, 링커 스크립트
  mm32f0162/    (동일 구조)
cmake/          툴체인 파일 및 MCU별 타겟 설정
```

## 계층 구조

```
firmware (EXECUTABLE)  ← app/main.cpp
  └─[PRIVATE]── bsp (OBJECT)       보드별 핀 배선
                  └─[PUBLIC]── mcu (OBJECT)        실리콘별 HAL 구현 + IRQ 벡터
                                 ├─[PUBLIC]── core_cm0 (OBJECT)  ARM CM0 아키텍처
                                 └─[PUBLIC]── hal (INTERFACE)    MCU-독립 인터페이스
```

각 계층은 CMake OBJECT 라이브러리로 구현되며, `app/`은 `bsp::` 와 `hal::` API만 사용합니다.

## 디버그 / 플래싱 (VS Code)

[Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) 확장이 필요합니다.

| 실행 구성 | 디버거 |
|-----------|--------|
| A31G123 (J-Link) | SEGGER J-Link |
| A31G123 (CMSIS-DAP) | OpenOCD |
| MM32F0162 (J-Link) | SEGGER J-Link |
| MM32F0162 (CMSIS-DAP) | OpenOCD |

OpenOCD 설정 파일: [`.vscode/openocd/`](.vscode/openocd/)

## 주요 구현 사항

- **벡터 테이블**: `.stack` → `.vectors`(CM0 예외) → `.vectors_<mcu>`(MCU IRQ) 순서로 링크
- **ISR 오버라이드**: 반드시 `extern "C" __attribute__((used)) void Handler()` 형태 사용  
  (릴리스 빌드 `-flto` 시 LTO 제거 방지)
- **C++ 제약**: `-fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics`
- **링커**: `-nostartfiles -nostdlib` + libgcc(`__aeabi_uidiv` 등 제공)
- **include 루트**: 프로젝트 루트 (`#include "hal/gpio.hpp"` 형태)

## 라이선스

MIT
