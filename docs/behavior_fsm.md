STATE: IDLE
------------------------------------
Entry Action: STOP, LED = BLUE
Transitions:
- Timer > 3s → PLAY

STATE: PLAY
------------------------------------
Entry Action: LED = GREEN
Transitions:
- Head < 7cm → SHY
- Head < 7cm AND Tail active → EVADE
- Otherwise → remain PLAY

STATE: SHY
------------------------------------
Entry Action: cautious motion pattern
Transitions:
- Completion → IDLE

STATE: EVADE
------------------------------------
Entry Action: aggressive escape motion
Transitions:
- Completion → IDLE

FAILSAFE
------------------------------------
Triggered by watchdog
Action: STOP + RED LED
