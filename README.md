# Producer-Consumer
Kent State CS33211 Operating Systems

This is the first programming assignment given to us in CS33211.
This assignment shows the use of a shared buffer using semaphores.

After multiple days working and researching on how to make the code work, i have not been able to get everything working correctly.
The program is supposed to have the producer produce numbers for a table and the consumer is supposed to wait for the producer to give a value.
Once this happens, the consumer is supposed to consume the value and leave an empty index in the table, which would repeat for 20 cycles.
Although im not certain, i believe the code that i submitted has an issue with the loop, most likely the sem_wait() command.
There are no syntax errors in either C file.
The prod/consum sharing is supposed to end after the 20th value has been consumed, but again, it is not working.
I hope that some credit is given based off of the effort and the code given.

Thank you for reading my README file.
