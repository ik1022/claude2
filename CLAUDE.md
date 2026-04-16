# CLAUDE.md

이 파일은 Claude Code(claude.ai/code)가 이 저장소에서 작업할 때 참조하는 가이드입니다.

## 프로젝트 개요

ARM Cortex-M0 MCU(ABOV A31G123, MindMotion MM32F0162)용 bare-metal C++ 펌웨어.
RTOS, CMSIS, 벤더 스타트업 파일 없음. CMake 타겟 선택만으로 동일한 앱 코드를 두 MCU에 빌드.

- **ABOV A31G123** — 64 KB Flash @ `0x00000000`, 4 KB SRAM, 최대 32 MHz
- **MindMotion MM32F0162** — 64 KB Flash @ `0x08000000`, 8 KB SRAM, 최대 72 MHz

## 빌드 명령

빌드 시스템: CMake + xPack Project Manager (xpm). 툴체인은 `xpm install`로 설치.

```bash
# Configure + 빌드 (설정 하나 선택)
xpm run prepare --config a31g123-release
xpm run build   --config a31g123-release

# 사용 가능한 설정: a31g123-debug, a31g123-release, mm32f0162-debug, mm32f0162-release
xpm run prepare --config mm32f0162-release
xpm run build   --config mm32f0162-release

# 전체 빌드 (4개 설정 모두)
xpm run test-all

# 클린
xpm run clean --config a31g123-release
xpm run clean   # 전체 클린

# 클럭 주파수 오버라이드
cmake ... -DMCU_CLOCK_HZ=16000000
```

빌드 결과물은 `build/<config>/`: `firmware` (ELF), `.hex`, `.lst`, `.sym`, `.map`.
`compile_commands.json`도 각 빌드 디렉터리에 생성됨 (clangd/IDE 언어 서버용).

## 디렉터리 구조

```
core_cm0/   ARM Cortex-M0 공통: stack.cpp, startup.cpp, handlers.cpp
            systick.hpp, nvic.hpp, scb.hpp  (코어 주변장치 레지스터 맵)
hal/
  gpio.hpp, clock.hpp, systick.hpp   MCU-독립 인터페이스 (별도 프로젝트로 분리 가능)
mcu/
  a31g123/  reg/gpio.hpp, reg/clock.hpp (실리콘 레지스터 맵)
            gpio.cpp, clock.cpp, systick.cpp (hal 인터페이스 구현)
            handlers.cpp, ld/a31g123.ld
  mm32f0162/ (동일 구조)
bsp/
  board.hpp         인터페이스: bsp::init(), bsp::led::PORT, bsp::led::PIN
  a31g123/board.cpp    보드별 핀 배선 + 초기화 시퀀스
  mm32f0162/board.cpp
app/
  main.cpp   애플리케이션 (MCU-독립, bsp:: 와 hal:: 만 사용)
cmake/
  arm-none-eabi.cmake      툴체인 파일
  target-a31g123.cmake     MCU 소스, 링커 스크립트, 클럭 주파수
  target-mm32f0162.cmake
```

## 계층 구조 (Layer Boundaries)

CMake OBJECT 라이브러리로 구현된 5개 계층:

```
firmware (EXECUTABLE)  ← app/main.cpp
  └─[PRIVATE]── bsp (OBJECT)       보드별 핀 배선
                  └─[PUBLIC]── mcu (OBJECT)        실리콘별 HAL 구현 + IRQ 벡터
                                 ├─[PUBLIC]── core_cm0 (OBJECT)  ARM CM0 아키텍처
                                 └─[PUBLIC]── hal (INTERFACE)    MCU-독립 인터페이스 헤더
```

- **core_cm0**: ARM 아키텍처 전용 — 벡터 테이블, 리셋 핸들러, SysTick/NVIC/SCB 레지스터 맵
- **hal**: MCU-독립 인터페이스 계약만 (`hal/*.hpp`). 구현 파일 없음. 별도 버전 프로젝트로 취급 가능
- **mcu/\<mcu\>**: MCU 전체 패키지 — 실리콘 레지스터 맵(`reg/`), HAL 구현(`gpio.cpp` 등), IRQ 벡터, 링커 스크립트
- **bsp**: 보드별 배선 — LED가 어느 핀인지, 보드 `init()` 시퀀스. 물리 보드당 `board.cpp` 하나
- **app**: 애플리케이션 코드. `bsp/`, `hal/`, `core_cm0/` 에서만 `#include`

> **주의**: CMake는 OBJECT 라이브러리의 객체 파일을 전이적으로 전달하지 않는다.
> `firmware`는 `core_cm0`, `mcu`, `bsp` 세 레이어를 모두 명시적으로 링크해야 한다.

## 핵심 기술 사항

**벡터 테이블 레이아웃** (링커가 순서대로 연결):
1. `.stack` — 초기 SP (`core_cm0/stack.cpp`)
2. `.vectors` — CM0 예외 1–15 (`core_cm0/handlers.cpp`)
3. `.vectors_<mcu>` — MCU IRQ 16+ (`mcu/<mcu>/handlers.cpp`)

**인터럽트 핸들러 선언 규칙**:
- 모든 핸들러(기본 weak 선언 및 오버라이드 모두)는 반드시 `extern "C"`를 사용해야 한다.
  `extern "C"` 없으면 C++ mangled 이름이 생성되어 벡터 테이블과 오버라이드가 연결되지 않는다.
- 릴리스 빌드는 `-flto` 사용. ISR 오버라이드는 반드시 `extern "C" __attribute__((used))`가 있어야 하며,
  LTO가 제거하지 않도록 `__attribute__((used))`는 `extern "C"` 뒤에 위치해야 한다.

```cpp
// 올바른 ISR 오버라이드 패턴
extern "C" __attribute__((used)) void SYSTICK_handler() {
    // 구현
}
```

**include 루트**: 프로젝트 루트가 include 루트. 모든 `#include` 경로는 프로젝트 루트 기준
(예: `#include "hal/gpio.hpp"`).

**MCU 선택**: CMake에 `-DTARGET_MCU=A31G123` 또는 `-DTARGET_MCU=MM32F0162` 전달
(xpm 설정이 자동으로 처리).

**링커 플래그**: `-nostartfiles -nostdlib` + `gcc`(libgcc)로 링크 — `__aeabi_uidiv` 등 제공.

**C++ 플래그**: `-fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics`
— 예외, RTTI, 스레드 로컬 스토리지 사용 금지.

**레지스터 정의**: `mcu/<mcu>/reg/*.hpp`의 `// !! Verify ... !!` 주석은 실제 데이터시트로
주소/비트필드 확인이 필요한 항목.

## 새 MCU 추가 절차

1. `mcu/<mcu>/reg/gpio.hpp`, `reg/clock.hpp` 생성
2. `mcu/<mcu>/gpio.cpp`, `clock.cpp`, `systick.cpp` 생성 (`hal/*.hpp` 구현)
3. `mcu/<mcu>/handlers.cpp` 생성 — 모든 핸들러 선언에 `extern "C"` 필수
4. `mcu/<mcu>/ld/<mcu>.ld` 생성
5. `bsp/<mcu>/board.cpp` 생성
6. `cmake/target-<mcu>.cmake` 생성 — 아래 변수 정의:
   - `MCU_LINKER_SCRIPT` — 링커 스크립트 경로
   - `MCU_DEFINE` — MCU 식별 매크로 (예: `MM32F0162`)
   - `MCU_CLOCK_HZ` — 기본 클럭 주파수
   - `MCU_SOURCES` — `mcu/<mcu>/` 소스 파일 목록 (핸들러 + HAL 구현 통합)
   - `MCU_BSP_SOURCES` — `bsp/<mcu>/` 소스 파일 목록

## 새 HAL 주변장치 추가 절차

1. `hal/<periph>.hpp`에 인터페이스 정의
2. `mcu/a31g123/<periph>.cpp` 및 `mcu/mm32f0162/<periph>.cpp` 구현
3. 각 `cmake/target-*.cmake`의 `MCU_SOURCES`에 두 파일 추가
