--this is the quick sort function in haskell
--I used GHC, macOS, vs code, "monday morning haskell", github, google ai overview for help/questions

--quick sort in haskelll due 0915

-- made sure it followed best case for time and space complexity: O(nlogn) & O(n)
--function from the assignment on canvas
qsort :: (Ord a) => [a] ->[a]
qsort [] = []
qsort (pivot:reset) = qsort slist ++ [pivot] ++ qsort llist
    where 
        --had to put "slist" & "llist" are different lines, got an error when I didn't
        slist = [x | x <- reset, x <= pivot]
        llist = [x | x <- reset, x > pivot]
--slist and llist are the lists
--resets <= pivot , & resets > pivots

--I took this from canvas
-- Call a sort function and print input and output.
testSort sort input = do
  putStr "Input:  "
  print input
  putStr "Sorted: "
  print (sort input)

-- Call some tests.
main = do
  putStrLn "CECS 342 Assignment 1"
  putStrLn "Name: Noor Kasem"
  putStrLn "Algorithm: quick sort, language: Haskell"
  
  testSort qsort ([]::[Int])
  testSort qsort [1]
  testSort qsort [3, 2, 1]
  testSort qsort [102, -43, 5, 645, 4, 34, -6, 776, 445, 45]
  testSort qsort ["the",  "quick",  "brown", "fox",
                  "jumps", "over", "the", "lazy", "dog"]

