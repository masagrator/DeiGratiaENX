This file contains informations about what lines were removed or altered in Switch release by devs in comparison to PC version.
This file won't include typo fixes.

# tl;dr
- Most of lines were deleted due to potential copyright claims (using words like Medabots or Pikachu). One line was altered to not relate to one of those lines.
- One line was removed because it didn't make sense from plot perspective to be there.
- Few lines were altered to fix discrepancies in passed time

# Full list

- `chapter3`:
  - Fixed lines:
    - PC:
      ```json
      {
          "JPN": "10分が経ち、20分が経った。",
          "ENG": "Ten minutes passed, then twenty."
      },
      ```
    - Switch
      ```json
      {
          "JPN": "5分が経ち、10分が経った。",
          "ENG": "Five minutes passed, then ten."
      },
      ```
- `chapter4_2`:
  - Fixed lines:
    - PC:
      ```json
      {
          "JPN": "「本来は、万が一どこかのサーバがダウンしても、20分以内にリカバリできると聞いています」",
          "ENG": "「We were told that if any of the servers went down, they would recover within 20 minutes.」"
      },
      ```
    - Switch:
      ```json
      {
          "JPN": "「本来は、万が一どこかのサーバがダウンしても、10分以内にリカバリできると聞いています」",
          "ENG": "「We were told that if any of the servers went down, they would recover within 10 minutes.」"
      },
      ```
- `chapter26`:
  - Removed lines:
    ```json
    {
        "JPN": "「自然界に広がる種子が物質を組織して生命を形作る……」",
        "ENG": "「That life could rise from nonliving material under the right circumstances.」"
    },
    {
        "JPN": "「概ね、メダロットと同じ仕組みですね」",
        "ENG": "「It's generally the same mechanism as in the Medabots, isn't it?」"
    },
    ```
    ```json
    {
      "JPN": "「ピカチュウが原初の生命という説が証明されたわけです」",
      "ENG": "「So the theory that Pikachu is primordial life has been proven.」"
    },
    ```
    ```json
    {
        "JPN": "「さよなら、ピカチュウ……」",
        "ENG": "「Goodbye, Pikachu...」"
    },
    {
        "JPN": "さっきからときわは何を言っているんだ。",
        "ENG": "Tokiwa had been talking to herself for a while now."
    },
    {
        "JPN": "いや、ときわが何を言っているのかわからないのはいつものことだから良いとして、",
        "ENG": "Well, not paying her words any mind was fine, but..."
    },
    {
        "JPN": "縁が何を言おうとしているのかもまるで伝わらない。",
        "ENG": "I couldn't even tell what Yukari was trying to say here."
    },
    ```
- `chapter29`:
  - Removed lines:
    ```json
    {
        "JPN": "まるで鉄腕アトム状態だ。",
        "ENG": "It was like the Astro Boy situation."
    },
    ```
- `chapter32_1`:
  - Removed lines:
    ```json
    {
        "JPN": "「そうだ、R2-D2を呼んでください」",
        "ENG": "「That's right, please call R2-D2.」"
    },
    {
        "JPN": "ここで古典スペースオペラか……",
        "ENG": "A classic space opera this time, huh..."
    },
    {
        "JPN": "なるほど閉塞感は似通っているが。",
        "ENG": "I see. The claustrophobic feeling was similar, though."
    },
    ```
  - Altered lines
    - PC:
      ```json
      {
          "JPN": "「呼ぶといえば、 POLは？」",
          "ENG": "「Speaking of calling, what about POL?」"
      },
      ```
    - Switch:
      ```json
      {
          "JPN": "「そうだ、 POLは？」",
          "ENG": "「Right, what about POL?」"
      },
      ```      
- `chapterR1`:
  - Removed lines:
    ```json
    {
        "JPN": "「それに光って、一体なんのことなの！？」",
        "ENG": "「And what do you mean by \"light?!\"」"
    },
    ```
- `chapterR8`:
  - Removed lines:
    ```json
    {
        "JPN": "「インターポールの銭形だ！」",
        "ENG": "「This is Zenigata from Interpol!」"
    },
    {
        "JPN": "「……いやいや」",
        "ENG": "「...Come on now.」"
    },
    ```
    ```json
    {
        "JPN": "「待てぇ！　ルパァアアン！」",
        "ENG": "「Wait! Lupiiiin!」"
    },
    ```
- `chapterR9`:
  - Removed lines:
    ```json
    {
        "JPN": "「GATCHA！」",
        "ENG": "「GATCHA!」"
    },
    ```
    ```json
    {
        "JPN": "思わず手を打ち、歓声を上げる。",
        "ENG": "I clapped my hands without thinking and cheered."
    },
    {
        "JPN": "科学忍者隊の面目躍如だ。",
        "ENG": "This was the majesty of the Science Ninja Team."
    },
    ```
- `chapterP_hiragino`:
  - Fixed lines
    - PC
      ```json
      {
  			"JPN": "9年前の、あの夜の惨劇を――。",
  			"ENG": "The tragedy of that night, nine years ago..."
  		},
  		{
  			"JPN": "――2045年8月4日。",
  			"ENG": "――August 4th, 2035."
  		},
      ```
    - Switch
      ```json
      {
  			"JPN": "7年前の、あの夜の惨劇を――。",
  			"ENG": "The tragedy of that night, seven years ago..."
  		},
  		{
  			"JPN": "――2026年4月4日。",
  			"ENG": "――April 4th, 2026."
  		},
      ```
- `chapterP_tokiwa`:
  - Changed lines
    - PC
      ```json
      {
			"JPN": "三種の神器、三原色、サンダーバード、サンバルカン。",
			"ENG": "The Three Sacred Treasures, the three primary colors, the thunderbird, and the Sun Vulcan."
		  },
      ```
    - Switch
      ```json
      {
			"JPN": "三種の神器、三原色。",
			"ENG": "The Three Sacred Treasures, the three primary colors."
		  },
      ```
