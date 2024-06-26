# DeiGratiaENX
`Dei Gratia no Rashinban` (デイグラシアの羅針盤) / `Compass of Dei Gratia` English translation mod for Nintendo Switch

This translation mod is based on PC mod from `kalitsu` that you can find here:<br>
https://vndb.org/r107637

# Installation

Mod is compatible only with version 1.0.1 of game.

Emulators are not supported by me, but it doesn't mean mod won't work with them.

1. Download DeiGratiaENX.zip from Releases, unpack it.
2. Copy `atmosphere` folder to the root of your sdcard, accepting any popup about overwriting folders
3. Run game

# Making mod manually

Requirements:
- Python 3.10+ (and library: `lzss`)

For plugin compilation you need:
- devkitpro (with `switch-dev` package installed)

To compile plugin, just run `make` inside plugin folder.<br>
To compile script run `sn/Prepare.cmd` on Windows or in bash opened in root of `sn` folder enter lines:
```cmd
python3 InjectText.py 
python3 sn_assembler_re.py
```

Copy `010071C00CBA4000` folder from `sn` folder to 
```
atmosphere/contents/
```
Copy `subsdk9` and `main.npdm` from `plugin/deploy` folder to
```
atmosphere/contents/010071C00CBA4000/exefs
```

Assets are available only from Release page.

# Notes
- Included differences in script between PC and Switch in [ScenarioChanges.md](./ScenarioChanges.md)
    - Except in two chapters, all removed texts were reimplemented. 
    - In `chapterR1` line was added by mistake in original scenario, so there was no reason to reimplement it back. 
    - `chapterR9` had lines related to anime brand that could lead to potential copyright issues (like most deleted lines), they are not important from plot perspective at all. Because engine is not understood well enough, it was not possible to reimplement them 1:1 with all sound and animation effects.
- Why plugin is necessary:
    - Replacing XTX textures with PNG on the fly
    - Changed available input first and last name length from 5 to 17 characters each
    - Changed name input keyboard to use only ASCII characters to avoid possible encoding issues
    - Changed calculations for text position in menu prompts to allow better centering
    - Translated hardcoded chapter names, notifications, Playing Log texts, song names, settings descriptions, scenario endings names, MC name checks
- Ported translation has some slight changes to better fit into how text is rendered in Regista engine + changed Saihoji to Saihouji to fit official romanization. Fixed also multiple typos from original mod.
- On top of porting original translation I have also:
    - redone subtitles for endings
    - translated texts in both openings
    - redone all scenario textures
    - translated textures unique to Switch release
    - replaced ascii glyphs in original font with glyphs rendered with Noto Sans Mono ExtraCondensed
- Reencoded videos are based on PC release because they are higher in both video and audio quality than Switch original videos

# Thanks to
- `kalitsu` for making translation mod (not involved with this project)
- `PhantomSonzai`, `badspot` and `wacker` for help with translating additional staff
