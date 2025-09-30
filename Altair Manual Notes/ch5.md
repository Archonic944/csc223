# Chapter 5 - Organization of CP/M

- In order to load the operating system, PROM contains I/O access primitives (drivers)
- But, those drivers are incomplete. The full drivers are stored in the CBIOS.
  - Vectors that point to disk/IO access primitives are stored in a specific area.
- User programs access all devices through the BDOS call vector. CBIOS vectors address primitive routines such as power up, rest, and device driver functions.
- 
