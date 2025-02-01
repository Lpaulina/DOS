The game rules are the following
  - Players can match 1 or 2 cards to a center card (e.g 3+4 to match a center card 7).
  - Color matches allow extra moves.
  - Double color match forces the opponent to draw an extra card.
  - If there is no match, the player draws from the deck.
  -First player to empty their hand wins.
Initial setup
  - Constants are defined such as MAXHAND = 50 & deckSize = 108
  - Linked list pointers are declared (p1head, p2head, chead)
  - The deck array is initialized with a file named CardDeck.txt
  - Asks the user whether or not to execute the shuffle function.
  - Deals 7 cards to each player and 2 cards to the center row.
Gameplay loop
  - Players take turns until someone wins, active player is determined by assigning the variable player either 1 or 2.
  - The center row constantly has at least 2 cards
  - The player tries to match a card from their hand to a center row card:
  - If matching, the card(s) are removed from hand and center
  - If they match in color, the player gets an extra move
  - If they match in both color and value, the opponent draws an extra card.
  - If no match, the player draws a card from the deck and adds one to the center row
  - If a player runs out of cards the game ends.
  - The other player’s remaining cards’ values determine the winner’s score
