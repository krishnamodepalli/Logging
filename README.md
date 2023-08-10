
# Logging in cpp made simple

Logging in cpp is usually made so complicated by all the developers, 
off-course it becomes more complex while going deeper, but I prefer to keep 
code and libraries very simple and clean, for the sake of easy life of 
understanding simple code.  

I am interested in some projects, where I want to use the Loggers, but 
unfortunately many loggers on the internet like spdlog & glog (by Google) are so
complicated and so annoying, So I wanted to make my own logger with the view of
glog as a Implementation reference. **Note: no code or methods are copied 
from the glog library, just the method references or maybe structure looks 
like that.** This is purely the sole implementation by [Krishna Modepalli](https://github.com/krishnamodepalli)
.  

I am also planning to add all the required functionalities of a basic and the
complex loggers soon. For now, just a basic logger.

> Usage and docs will be loaded soon.  

> **Declaimer** : *This Logger is now thread safe.*

## TODO:
- [X] Add synchronization / thread_safety
- [ ] Add colors and time for the logger
- [ ] Add file logging, also rotated logging
