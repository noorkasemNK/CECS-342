--Noor Kasem cecs 342-03
--due 0929
--I used my macos, vs code, GHC compiler, gemini/google ai overview, haskell.org, tutorials point, claude extension

module Main where

merge :: (Ord a) => [a] -> [a] -> [a]
merge [] noor = noor
merge kasem [] = kasem
merge (x:kasem) (y:noor)
  | x <= y    = x : merge kasem (y:noor)
  | otherwise = y : merge (x:kasem) noor

splitInHalf :: [a] -> ([a], [a])
splitInHalf kasem = splitAt (length kasem `div` 2) kasem

msort :: (Ord a) => [a] -> [a]
msort []  = []
msort [x] = [x]
msort kasem  = merge (msort back) (msort front)
  where
    (back, front) = splitInHalf kasem


testSort :: (Show a) => ([a] -> [a]) -> [a] -> IO ()
testSort sortFn input = do
  putStr "Input:  "
  print input
  putStr "Sorted: "
  print (sortFn input)

--main :: IO ()
main = do
  putStrLn "CECS 342 Assignment 4"
  putStrLn "Name: Noor Kasem"
  putStrLn "Algorithm: merge sort, Language: Haskell"
  
  testSort msort ([] :: [Int])
  testSort msort [1]
  testSort msort [3, 2, 1]
  testSort msort [102, -43, 5, 645, 4, 34, -6, 776, 445, 45]
  testSort msort ["the", "quick", "brown", "fox",
                  "jumps", "over", "the", "lazy", "dog"]