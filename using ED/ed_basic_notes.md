# CP/M `ED`: quick command table & workflows

Version in use
- Matches Digital Research **ED** as shipped with CP/M **1.4–2.2** (features in the excerpt align with the ED User’s Manual and 2.x reference cards; `V`/`-V` line-number toggle and `#A` appear there).

## Commands (sorted by “you’ll use this most” → least)
| Cmd | What it does | Notes / example |
|---|---|---|
| `I` | Insert (enter input mode) | End with **CTRL-Z** to return to command mode. |
| `CTRL-Z` | End insert / string terminator | Used to end `I` input and to delimit `S` (substitute) strings. |
| `E` | End edit, **write** changes, exit to CCP | Creates/updates `.BAK` and saves new file. |
| `#A` | **Append entire file** into buffer | `#` = 65535 lines → practical “read all”. |
| `B` | Set pointer to **Beginning** of buffer | Often followed by `T` to type from top. |
| `T` / `nT` | **Type** (list) current line / `n` lines | E.g., `8T` after `B` types 8 lines. |
| `nL` | Move **down `n` lines** | E.g., `3L T` moves 3 lines then types current. |
| `S old^Z new^Z` | **Substitute** text on current line | Often followed by `0 L T` to re-type line. |
| `0` (zero) | Address **start of current line** | Used in combos like `0 L T`. |
| `V` / `-V` | Show line numbers / turn off | Useful for proofing; some builds boot with numbering on. |
| `U` / `-U` | Force upper-case on input / cancel | Helps keep ASM sources uppercase. |
| `A` / `nA` | **Append** `n` lines from disk | Building buffer in chunks when not using `#A`. |
| `W` / `nW` | **Write** `n` lines to temp file | Used in huge files to manage buffer. |
| `O` | Open **new file** from temp (like save-and-reopen) | “Head of new file” after auto-`E`. |
| `H` | **Return** to original source, discard temp | Undo current edit session. |
| `Q` | **Quit without saving** | Bail-out if you’ve messed up the buffer. |
| `R` | **Read library** lines (xfer file) | Pair with `X`/`K` for line libraries. |
| `X` | **Transfer** selected lines to xfer file | Re-read later with `R`; clear via `0X`. |
| `K` | **Kill** (delete) current line(s) | Common with `X` workflows. |

> Tip: Commands can be **strung**: e.g., `S MIV^Z MVI^Z 0 L T` = substitute, go to start of line, move down one line, type.

---

## Sample ED workflows

### 1) Create `TEST.ASM` from scratch (as in class excerpt)
1. `ED TEST.ASM` → `I`  
2. Type the program; **CTRL-Z** to finish insert.  
3. `B 8 T` to review; `-V` if numbering is on.  
4. `E` to save & exit.

### 2) Fix a typo you spot on line 4
1. `ED TEST.ASM` → `#A` → `B`  
2. `3 L T` (down three, show it)  
3. `S MIV^Z MVI^Z 0 L T` (patch & verify)  
4. `E`

### 3) Re-open, duplicate buffer by accident, safely abort
1. `ED TEST.ASM` → `#A` → `#A` (oops, appended twice)  
2. `Q` (quit without writing)  
3. Re-enter: `ED TEST.ASM` → `#A` (once), optional `V` to show line numbers, `E` when done.
