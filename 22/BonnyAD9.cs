// .NET version: 6.0

using System.Collections;

BinaryTree<int> tree = new() { 5, 9, 2, 6, 16, -89 };

Console.WriteLine(string.Join(' ', tree)); // -89 2 5 6 9 16
tree.Reverse(); // recursive version
Console.WriteLine(string.Join(' ', tree)); // 16 9 6 5 2 -89
tree.ReverseNR(); // not recursive version
Console.WriteLine(string.Join(' ', tree)); // -89 2 5 6 9 16


// C# doesn't have a BinaryTree implementation
class BinaryTree<T> : IEnumerable<T> where T : IComparable
{
    private BinaryTreeNode<T>? _tree;
    public BinaryTreeNode<T>? Tree
    {
        get => _tree;
        set => _tree = value;
    }

    public void Add(T item) => BinaryTreeNode<T>.Find(ref _tree, item) ??= new(item);
    public void Reverse() => Tree?.Reverse();

    public void ReverseNR() // not recursive version
    {
        Stack<BinaryTreeNode<T>> s = new();

        var cur = Tree;

        while (cur is not null || s.Count > 0)
        {
            cur ??= s.Pop();

            (cur.Left, cur.Right) = (cur.Right, cur.Left);

            if (cur.Left is not null)
                s.Push(cur.Left);

            cur = cur.Right;
        }
    }

    public IEnumerator<T> GetEnumerator() => Tree?.GetEnumerator() ?? Enumerable.Empty<T>().GetEnumerator();
    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
}

class BinaryTreeNode<T> : IEnumerable<T> where T : IComparable
{
    private BinaryTreeNode<T>? _left;
    public BinaryTreeNode<T>? Left
    {
        get => _left;
        set => _left = value;
    }

    private BinaryTreeNode<T>? _right;
    public BinaryTreeNode<T>? Right
    {
        get => _right;
        set => _right = value;
    }

    public T Item { get; set; }

    public BinaryTreeNode(T item)
    {
        Item = item;
    }

    public static ref BinaryTreeNode<T>? Find(ref BinaryTreeNode<T>? node, T item)
    {
        if (node is null || node.Item.CompareTo(item) == 0)
            return ref node;

        if (node.Item.CompareTo(item) > 0)
            return ref Find(ref node._left, item);
        return ref Find(ref node._right, item);
    }

    public void Reverse()
    {
        (Left, Right) = (Right, Left);
        Left?.Reverse();
        Right?.Reverse();
    }

    public IEnumerator<T> GetEnumerator()
    {
        if (Left is not null)
        {
            foreach (var v in Left)
                yield return v;
        }

        yield return Item;

        if (Right is not null)
        {
            foreach (var v in Right)
                yield return v;
        }
    }

    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
}
