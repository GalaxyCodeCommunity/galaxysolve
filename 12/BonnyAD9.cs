// .NET version: 6.0

using System.Text.Json;

Translator t = JsonSerializer.Deserialize<Translator>(File.ReadAllText("languages.json"))!;

Console.WriteLine(t.Translate("dog", "cs"));
Console.WriteLine(t.Translate("cat", "cs", 2));
Console.WriteLine(t.Translate("human", "en", 10));

record Translator(Language[] Languages)
{
    public string Translate(string word, string lang, int count = 1)
    {
        int i = Array.FindIndex(Languages, p => p.ID == lang);
        if (i == -1)
            return word;

        Word? w = null;
        foreach (var l in Languages)
        {
            if ((w = l.GetWord(word)) is not null)
                break;
        }

        if (w is null)
            return word;

        Word? t = Languages[i].GetWord(w.ID);

        return t?.Shapes[count >= t.Shapes.Length ? 0 : count] ?? word;
    }
}

record Language(string ID, Word[] Words)
{
    public Word? GetWord(string word) => Words.FirstOrDefault(p => p.Shapes.Contains(word));
    public Word? GetWord(int ID) => Words.FirstOrDefault(p => p.ID == ID);
}

record Word(int ID, string[] Shapes);

/* contents of languages.json:
{
  "Languages": [
    {
      "ID": "cs",
      "Words": [
        {
          "ID": 1,
          "Shapes": [
            "psů",
            "pes",
            "psi",
            "psi",
            "psi"
          ]
        },
        {
          "ID": 2,
          "Shapes": [
            "koček",
            "kočka",
            "kočky",
            "kočky",
            "kočky"
          ]
        },
        {
          "ID": 3,
          "Shapes": [
            "lidí",
            "člověk",
            "lidi",
            "lidi",
            "lidi"
          ]
        }
      ]
    },
    {
      "ID": "en",
      "Words": [
        {
          "ID": 1,
          "Shapes": [
            "dogs",
            "dog"
          ]
        },
        {
          "ID": 2,
          "Shapes": [
            "cats",
            "cat"
          ]
        },
        {
          "ID": 3,
          "Shapes": [
            "humans",
            "human"
          ]
        }
      ]
    }
  ]
}
*/
