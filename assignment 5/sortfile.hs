--all the tools I used haskell.org, google gemini ai overview, w3schools, geeks4geeks, mac os, ghc compiler, vs code/claude extension for debugging

module Main where
 --imports
 
import Data.List (sort, sortBy)
import Data.Ord (comparing, Down(..))
import Text.Printf (printf)
 
 --haskell version of a struct
data Person = Person
  { name :: String
  , age  :: Int
  } deriving (Show, Eq)
 
numbers :: [Double]
numbers =
  [ 645.41, 37.59, 76.41, 5.31, -34.23, 1.11
  , 1.10, 23.46, 635.47, -876.32, 467.83, 62.25 ]
 
people :: [Person]
people =
  [ Person "Hal" 20,      Person "Susann" 31,  Person "Dwight" 19
  , Person "Kassandra" 21, Person "Lawrence" 25, Person "Cindy" 22
  , Person "Cory" 27,     Person "Mac" 19,     Person "Romana" 27
  , Person "Doretha" 32,  Person "Danna" 20,   Person "Zara" 23
  , Person "Rosalyn" 26,  Person "Risa" 24,    Person "Benny" 28
  , Person "Juan" 33,     Person "Natalie" 25 ]
 --the values were copied and pasted from canvas
-- :: 

sortNumbersAsc :: [Double] -> [Double]
sortNumbersAsc = sort
sortPeopleByName :: [Person] -> [Person]
sortPeopleByName = sortBy (comparing name)
sortPeopleByAgeDescThenName :: [Person] -> [Person]
sortPeopleByAgeDescThenName = sortBy (comparing (Down . age) <> comparing name)
printPeople :: [Person] -> IO ()
printPeople = mapM_ (\p -> printf "  %-10s %d\n" (name p) (age p))
--ascending order for numbers, ascending order for names, descending order for age and then ascending order for names

--main function test your code and display the sorted results in the console.
main :: IO ()
main = do
  putStrLn "Numbers sorted ascending:"
  putStrLn $ "  " ++ show (sortNumbersAsc numbers)
 
  putStrLn "\nPeople sorted by name:"
  printPeople (sortPeopleByName people)
 
  putStrLn "\nPeople sorted by age (descending), then name:"
  printPeople (sortPeopleByAgeDescThenName people)