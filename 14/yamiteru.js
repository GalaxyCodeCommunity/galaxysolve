const SYMBOLS = {
		".-": "A",
    "-...": "B",
    "-.-.": "C",
    "-..": "D",
    "."  : "E",
    "..-.": "F",
    "--.": "G",
    "....": "H",
    "..": "I",
    ".---": "J",
    "-.-": "K",
    ".-..": "L",
    "--": "M",
    "-.": "N",
    "---": "O",
    ".--.": "P",
    "--.-": "Q",
    ".-.": "R",
    "...": "S",
    "-"  : "T",
    "..-": "U",
    "...-": "V",
    ".--": "W",
    "-..-": "X",
    "-.--": "Y",
		"--..":  "Z"
};

function translate(value) {
	return value
		.split("  ")
		.map((w) => w 
				.split(" ")
				.map((l) => SYMBOLS[l])
				.join("")
		)
		.join(" ");
}

console.log(
	translate("..  .-.. --- ...- .  -.-- --- ..-")
);

module.exports = translate;
