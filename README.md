# StudentHelp – Peer Skill & Study Matching System

## Contributor
- **Name:** Ahmad Raza
- **Roll Number:** 26K-0609
- **Assigned part:** Subject searching and the peer-matching algorithm

## Files
- `studenthelp.c` – Implements case-insensitive student ID and subject matching, teacher searching, full/partial matching, and mutual study partner matching.
- `studenthelp.h` – Defines the `Student` structure and declares the public functions.

## Functions
- `findStudent()` – Finds a student by ID and returns their array index, or `-1` if not found.
- `searchTeacher()` – Lists students who can teach a requested subject.
- `showMatch()` – Displays students who can teach all or some of a student's required subjects.
- `showPartners()` – Finds pairs of students who can help each other.

## Integration note
This is Ahmad Raza's assigned module, not the complete group application. The group's main program must use the same `Student` structure from `studenthelp.h` and call these functions.

## Compile
After the group's `main.c` is integrated with this module, compile with:

```bash
gcc main.c studenthelp.c -o StudentHelp
```
