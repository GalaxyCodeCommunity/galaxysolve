using System.Text.RegularExpressions;

Console.WriteLine(ParseUri("https://localhost:8000/foo/baz?bar=baz"));
// URI { Scheme = https, Host = localhost, Port = 8000, Path = /foo/baz, Query = bar=baz, Fragment =  }

static URI ParseUri(string str)
{
    var m = Regex.Match(str, @"(?<scheme>[A-Za-z][A-Za-z1-9\+\.\-]*):(//(?<host>[^:/\?#]*)(:(?<port>[^/\?#]*))?)?(?<path>/[^\?#]*)?(\?(?<query>[^#]*))?(#(?<fragment>.*))?");
    
    if (!m.Success)
        throw new FormatException("'str' had incorrect format");

    var g = m.Groups;

    return new(
        g.GetValueOrDefault("scheme")!.Value,
        g.GetValueOrDefault("host")?.Value,
        g.GetValueOrDefault("port")?.Value,
        g.GetValueOrDefault("path")?.Value ?? "",
        g.GetValueOrDefault("query")?.Value,
        g.GetValueOrDefault("fragment")?.Value
    );
}

record URI(string Scheme, string? Host, string? Port, string Path, string? Query, string? Fragment);
