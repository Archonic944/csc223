# CP/M `ED` - Command Reference & Sample Workflows (CORRECTED)

## Commands & Notes

### Essential Commands (Learn These First)

| Cmd | What it does | Notes / usage details |
|---|---|---|
| `I` / `i` | Enter **insert mode** | Type text. Finish with **CTRL-Z** to return to command mode. Use lowercase `i` to allow mixed case input; uppercase `I` forces all input to uppercase. |
| `E` | **End edit** (save & exit) | Writes buffer to disk, appends any remaining source lines; previous version becomes `.BAK`. |
| `Q` | **Quit without saving** | Abort the edit session; discard buffer changes. |
| `#A` | Append entire file from disk | `#` means 65535. Loads all unread lines from source file into buffer. Most common way to start editing. |
| `±nT` | **Type** lines | `0T` types from line start to CP; `T` or `1T` types from CP to line end; `nT` (n>1) types current line + next n-1 lines. |
| `±nL` | Move **up/down `n` lines** | `+nL` or `nL` moves down; `-nL` moves up. Default `n=1`. Primary navigation command. |
| `±nK` | **Kill** (delete) lines | Deletes `n` lines. `+nK` or `nK` deletes forward; `-nK` deletes backward. |

### Basic Editing Commands

| Cmd | What it does | Notes / usage details |
|---|---|---|
| `nSs1^Zs2^Z` | **Substitute** `s1` → `s2` | Substitutes string `s1` with `s2` on next `n` occurrences. Use CTRL-Z as delimiter. Use lowercase `s` for mixed case. |
| `±nD` | **Delete** `n` characters | `+nD` deletes forward; `-nD` deletes backward from CP. |
| `nFs^Z` | **Find** string `s` | Searches for `s` starting at CP. Moves CP after string if found. `n` = number of occurrences. |
| `Is^Z` | **Insert** string `s` | Inserts `s` at CP. Terminated by `^Z` (no newline) or `<cr>` (adds newline). |
| `±nC` | **Move** character positions | Moves CP by `n` characters. `+` moves forward, `-` moves backward. |
| `0L` | Move CP to start of **current line** | Note: command is `0L` (zero-L), not just `0`. |

### Navigation & Positioning

| Cmd | What it does | Notes / usage details |
|---|---|---|
| `±B` | Move CP to **beginning** (`+B`) or **bottom** (`-B`) | Reset position before listings or edits. |
| `n:` | Move to **absolute line** `n` | Example: `345:T` moves to line 345 and types it. Use `:n` for relative offset from current line. |
| `n1::n2` | **Range** from absolute `n1` to `n2` | Example: `345::400T` moves to line 345, then types through line 400. |
| `0L T` | Move CP to line start, then type to end | Common sequence: `0L` positions at start, `T` types rest of line. |
| `±n` | Move and type | Shorthand for `±nLT`. Moves `n` lines and types one line. |

### Large File Management

| Cmd | What it does | Notes / usage details |
|---|---|---|
| `A` / `nA` | Append `n` lines from disk | Use when file is large or buffer-limited. Default `n=1`. |
| `nW` | Write `n` lines to temp file | Writes first `n` lines from buffer to temporary output file, shifts remaining lines up. |
| `nNs^Z` | **Next** occurrence with auto-scan | Like `F` but automatically writes/appends to search entire source file. |

### Advanced Features

| Cmd | What it does | Notes / usage details |
|---|---|---|
| `nX` | **Transfer** `n` lines to X$$$.LIB | Saves lines to temporary transfer file without removing them from buffer. |
| `R` | **Read** from transfer file or library | With no filename, reads X$$$.LIB. With filename (e.g., `RMACRO^Z`), reads MACRO.LIB. |
| `nJs1^Zs2^Zs3^Z` | **Juxtapose** strings | Finds `s1`, inserts `s2`, deletes up to `s3`. Repeated `n` times. |
| `nMcs^Z` | **Macro** command | Executes command string `cs` a total of `n` times (or until error if `n=0` or `1`). |
| `H` | **Move to head** of new file | Performs automatic `E`, then reopens result as new source file. Like saving and re-editing. |
| `O` | **Return to original** source file | Empties buffer, deletes temporary file, resets to start of source. Discards all edits. |
| `V` / `-V` | Turn line numbering on / off | `V` enables line number display; `-V` disables it. `0V` shows buffer statistics (free/total bytes). |
| `U` / `-U` | Force upper-case / cancel | `U` translates input to uppercase; `-U` disables translation. |
| `nZ` | **Sleep** (wait) | Pauses approximately `n` seconds. |
| `DEL` / `RUBOUT` / `CTRL-H` | Backspace/delete character | Erases last character typed at console. |

---

## Major Corrections from Original Table

**WRONG in original:**
- **`0`** (zero alone) — Does NOT exist as a command. Use **`0L`** to move CP to line start.
- **`O`** — Does NOT "open new file from temp." It **returns to original source file**, discarding all edits.
- **`H`** — Does NOT "return to original." It **saves and reopens** the edited file as new source (move to "head" of new file).
- **`nL`** — Can move **up** with `-nL` or **down** with `+nL`, not just down.
- **`T`** descriptions were misleading about what `T` vs `0T` vs `nT` do.

---

## Sample Workflows

### 1. Create a new file `TEST.ASM`
```
ED TEST.ASM
i                ; lowercase i for mixed-case input
  <type source lines>
CTRL-Z
B 8T             ; move to beginning, type 8 lines
-V               ; turn off line numbering if needed
E
```

### 2. Fix a typo on line 4 (e.g., "MIV" → "MVI")
```
ED TEST.ASM
#A               ; append entire file
B                ; move to beginning
3L               ; move down 3 lines (now at line 4)
0L T             ; position at line start, type the line
Ss MIV^Z MVI^Z   ; substitute (use lowercase s)
0L T             ; verify the change
E
```

### 3. Abort after appending the file twice by mistake
```
ED TEST.ASM
#A
#A               ; accidentally duplicated
Q                ; quit without saving
ED TEST.ASM
#A
E
```

### 4. Delete lines 10-15
```
ED TEST.ASM
#A
B 9L             ; move to line 10
6K               ; kill 6 lines
E
```

### 5. Search and replace all "GAMMA" with "DELTA"
```
ED TEST.ASM
#A
B                ; start at beginning
MSGAMMA^ZDELTA^Z0LT^Z  ; macro: substitute, move to line start, type
E
```

---

## Key Points from CP/M 2.2 Manual

- **Character Pointer (CP)** is always between characters, at line start, or at buffer end
- **Default n=1** when number omitted (e.g., `T` = `1T`, `L` = `1L`)
- **`#` means 65535** (effectively "all")
- **Colon (`:`) for absolute addressing:** `345:T` moves to line 345; `:400T` types through line 400; `345::400T` moves to 345, types through 400
- **Line numbers are temporary** — they change after edits and are not saved to file
- **Uppercase commands** force uppercase input/strings
- **Must be in command mode** to issue commands (exit insert with CTRL-Z)
- **`X` command doesn't remove** lines from buffer (use `K` afterward if needed)
- **Single-letter safety:** Commands `E`, `H`, `O`, `Q` must be typed alone, not in command strings
