# 테세우스와 미노타우로스 미로 탈출 프로그램

## 프로젝트 개요

이 프로젝트는 그리스 신화에서 유래된 **테세우스와 미노타우로스** 미로 게임을 C 언어로 구현한 프로그램입니다. 테세우스가 미노타우로스로부터 도망쳐 미로에서 탈출하는 최적 경로를 찾는 알고리즘 문제를 해결합니다.

## 게임 규칙

- **테세우스(T)**: 플레이어 캐릭터로, 미로에서 탈출구(E)로 도달해야 합니다.
- **미노타우로스(M)**: 테세우스를 추적하는 몬스터로, 매 턴마다 테세우스에게 가까워지려고 합니다.
- **탈출구(E)**: 테세우스가 도달해야 하는 목표 지점입니다.
- **벽(#)**: 이동할 수 없는 장애물입니다.
- **공간( )**: 이동 가능한 영역입니다.

### 이동 규칙
- 테세우스는 상하좌우로 2칸씩 이동하거나 제자리에 머물 수 있습니다 (R, L, U, D, S).
- 미노타우로스는 테세우스를 향해 매 턴마다 최대 2칸씩 이동합니다.
- 테세우스와 미노타우로스가 같은 위치에 있으면 게임이 종료됩니다 (테세우스 패배).

## 프로젝트 구조

```
theseus_minotaur/
├── theseus/
│   └── HW3_2019707048.c    # 메인 프로그램 소스 코드
└── README.md               # 프로젝트 설명서
```

## 주요 기능

### 1. 미로 정의
- 10개의 서로 다른 미로가 하드코딩되어 있습니다.
- 각 미로는 서로 다른 크기와 난이도를 가집니다.
- 미로 크기: 9×10부터 21×31까지 다양

### 2. 알고리즘
- **BFS (너비 우선 탐색)** 알고리즘을 사용하여 최적 경로를 찾습니다.
- 상태 공간 탐색: (테세우스 위치, 미노타우로스 위치)의 조합을 상태로 정의
- 중복 상태 검사를 통해 효율성을 개선

### 3. 주요 함수들

#### `solve_maze(int maze_index)`
- 특정 미로를 해결하는 메인 함수
- 테세우스, 미노타우로스, 탈출구의 초기 위치를 찾습니다.

#### `bfs(State start, int (*stop_condition)(Position), int maze_index)`
- BFS 알고리즘의 핵심 구현
- 가능한 모든 상태를 탐색하여 해결책을 찾습니다.

#### `next_minotaur_position(Position theseus, Position minotaur, int maze_index)`
- 미노타우로스의 다음 위치를 계산
- 테세우스에게 가장 가까워지는 방향으로 이동

#### `next_theseus_states(Position pos, Position next_states[5], char moves[5], int maze_index)`
- 테세우스가 이동할 수 있는 모든 가능한 위치를 계산
- 5가지 행동: 우(R), 하(D), 좌(L), 상(U), 정지(S)

## 컴파일 및 실행

### 컴파일
```bash
cd theseus
gcc -o maze_solver HW3_2019707048.c
```

### 실행
```bash
./maze_solver
```

## 출력 형식

프로그램은 각 미로에 대해 다음과 같이 출력합니다:

```
test 1:
solution found
R R D D L L 

test 2:
solution found
R S R R 

Maze 1:
solution found
U U L L L L L L U U U U L L 
```

- **test 1-3**: 첫 3개의 테스트 케이스
- **Maze 1-7**: 나머지 7개의 미로
- 해결책이 있는 경우: 이동 명령어 시퀀스 출력
- 해결책이 없는 경우: "No solution" 출력

## 알고리즘 복잡도

- **시간 복잡도**: O(W × H × W × H) = O(W²H²)
  - W: 미로의 너비, H: 미로의 높이
  - 가능한 모든 (테세우스, 미노타우로스) 위치 조합을 탐색

- **공간 복잡도**: O(W²H²)
  - BFS 큐와 방문 상태 저장을 위한 공간

## 개발 정보

- **개발자**: 정상기 (학번: 2019707048)
- **과목**: 알고리즘
- **언어**: C
- **개발 환경**: 표준 C 라이브러리 사용

## 특징

1. **완전한 상태 공간 탐색**: BFS를 통해 최적해 보장
2. **다양한 미로 지원**: 10개의 서로 다른 난이도의 미로
3. **효율적인 중복 검사**: 동일한 상태의 재방문을 방지
4. **직관적인 출력**: 이동 명령어를 문자로 표현 (R, L, U, D, S)

## 한계 및 개선점

- 미로가 하드코딩되어 있어 동적으로 미로를 입력받을 수 없음
- 메모리 사용량이 큰 미로에서는 비효율적일 수 있음
- GUI 없이 텍스트 기반 출력만 제공

이 프로그램은 게임 이론과 그래프 탐색 알고리즘의 실제 적용 사례를 보여주는 교육적 가치가 높은 프로젝트입니다. 