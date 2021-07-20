# OS-Mutex_Semaphore
Implementation of Mutex, Semaphore and Reader &amp; Writer Lock for Operation System course task.

   Mutex: 
    
    Using __𝑠𝑦𝑛𝑐_𝑏𝑜𝑜𝑙_𝑐𝑜𝑚𝑝𝑎𝑟𝑒_𝑎𝑛𝑑_𝑠𝑤𝑎𝑝 builtin.
  
    Test runs 10k threads in parallel. Every thread does a ++ operation on variable x. 
    When argv[1] is not passed it runs the test without Mutex, The result should be close to 10k 
    but in most times will not be exactly 10k. Use argv[1] = 1 to activate the test with Mutex, 
    then the result should be exactly 10k. 
  
   Counting Semaphore:
    
    Using Barz implementation for Counting Semaphore (1983) - Using binary semaphores.
    
    Test runs 10k threads in parallel too, but at this test every tread does 10 times ++ operation. 
    In this test pass argv[1] is required always (value of Counting Semaphore = argv[1]). 
    Then when you will pass 1 as value you will expect to see 100k as the output. 
    As the value of the semaphore will be bigger you expect to see the output a little bit 
    moving away below 100k.
    
   Reader/Writer:
    
    A test case that I found on Github. It runs 10 Readers and 5 Writers.
    link:
    https://github.com/codophobia/readers-writers-solution-in-c/blob/master/reader-writer.c
