// comments of what I used and did in other file


using System;
using System.Collections.Generic;
using System.Globalization;
namespace GenericSort;

public record Person(string Name, int Age);

public static class Program

{ private static readonly List<double> numbers = new()
{ 645.41, 37.59, 76.41, 5.31, -34.23, 1.11,
        1.10, 23.46, 635.47, -876.32, 467.83, 62.25
    };
    private static readonly List<Person> people = new()
    {
        new("Hal", 20), new("Susann", 31), new("Dwight", 19), new("Kassandra", 21),
        new("Lawrence", 25), new("Cindy", 22), new("Cory", 27), new("Mac", 19),
        new("Romana", 27), new("Doretha", 32), new("Danna", 20), new("Zara", 23),
        new("Rosalyn", 26), new("Risa", 24), new("Benny", 28), new("Juan", 33),
        new("Natalie", 25)
    };

    private static List <T> SortedCopy<T>(IEnumerable<T> source, Comparison<T> compare)
    {
        var copy = new List<T>(source);
        copy.Sort(compare);
        return copy;
    }
        private static int CompareNumbersAsc(double a, double b) => a.CompareTo(b);
        private static int ComparePeopleByName(Person a, Person b) => string.CompareOrdinal(a.Name, b.Name);

        private static int ComparePeopleByAgeDescThenName(Person a, Person b)
    {
        int byAge = b.Age.CompareTo(a.Age); 
        return byAge != 0 ? byAge : string.CompareOrdinal(a.Name, b.Name);
}
private static void PrintNumbers(IEnumerable<double> values)
    {
        foreach (var n in values)
            Console.WriteLine($"  {n.ToString("F2", CultureInfo.InvariantCulture)}");
    }

    private static void PrintPeople(IEnumerable<Person> values)
    {
        foreach (var p in values)
            Console.WriteLine($"  {p.Name,-10} {p.Age}");
    }

    public static void Main()
    {
        Console.WriteLine("Numbers sorted ascending:");
        PrintNumbers(SortedCopy(numbers, CompareNumbersAsc));

        Console.WriteLine("\nPeople sorted by name:");
        PrintPeople(SortedCopy(people, ComparePeopleByName));

        Console.WriteLine("\nPeople sorted by age (descending), then by name:");
        PrintPeople(SortedCopy(people, ComparePeopleByAgeDescThenName));
    }
}