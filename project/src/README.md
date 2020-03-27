#Lab 2: Binky-Buzzy Toy

By Robert Marc

For this project, I design my toy as such:

SW1: This is the default state the toy goes to on load. It activates both red
and green LEDs and dims them.
SW2: This switch acts as a "halt" state. It halts the machine in the state and
substate that it was in when pressed. This means that whatever LEDs were on
remain on and whatever tone was being played on the buzzer continues to play.
SW3: This switch plays 'Mary Had a Little Lamb' on repeat. For this song,
the red LED blinks to the beat of the song. The green LED turns on when a note
is played and stays on for the length that the note is played.
SW4: This switch transitions through a simple four step state machine. It
plays a different note and activates different LEDs for each state.
