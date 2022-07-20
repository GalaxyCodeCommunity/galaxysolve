struct Pair<'a>(&'a str, &'a str);
static DECODER_MAP: &'static [Pair] = &[
    Pair(".-",   "A"),
    Pair("-...", "B"),
    Pair("-.-.", "C"),
    Pair("-..",  "D"),
    Pair(".",    "E"),
    Pair("..-.", "F"),
    Pair("--.",  "G"),
    Pair("....", "H"),
    Pair("..",   "I"),
    Pair(".---", "J"),
    Pair("-.-",  "K"),
    Pair(".-..", "L"),
    Pair("--",   "M"),
    Pair("-.",   "N"),
    Pair("---",  "O"),
    Pair(".--.", "P"),
    Pair("--.-", "Q"),
    Pair(".-.",  "R"),
    Pair("...",  "S"),
    Pair("-",    "T"),
    Pair("..-",  "U"),
    Pair("...-", "V"),
    Pair(".--",  "W"),
    Pair("-..-", "X"),
    Pair("-.--", "Y"),
    Pair("--..", "Z")
];


fn decode(s: &str) {
    let a: String = s.split("|").map(|c| {
        for x in DECODER_MAP {
            if c == x.0 { return x.1; }
        }
        return "?";
    }).collect();
    println!("{}", a);
}

fn main() {
    decode(".-.|.|..-|...|.|-.-");
}
