import json
import glob
from pathlib import Path
import os

files = glob.glob("Patches/*.json")
os.makedirs("Patched", exist_ok=True)

for i in range(len(files)):
	print(files[i])
	file = open(files[i], "r", encoding="UTF-8")
	patch = json.load(file)
	file.close()
	
	file = open(f"jsons/{Path(files[i]).stem}.json", "r", encoding="UTF-8")
	DUMP = json.load(file)
	file.close()
	
	y = 0
	for x in range(len(DUMP["COMMANDS"])):
		if (DUMP["COMMANDS"][x]["LABEL"] == patch[y]["LABEL"]):
			DUMP["COMMANDS"][x] = patch[y]
			y += 1
			if (y == len(patch)):
				break
	
	assert(y == len(patch))

	new_file = open(f"Patched/{Path(files[i]).stem}.json", "w", encoding="UTF-8")
	json.dump(DUMP, new_file, indent="\t", ensure_ascii=False)
	new_file.close()