
# `klog` - A modern & simple cpp Logging library.

I am a CS student, I want things simple. I don't want to make things complicated
or too sophisticated. I am working on a project where I need to work with 
loggers, so exploring the internet gave me options like `spdlog` & `glog` by 
google. These may be good, but I thought they are so complicated and too 
much to handle for me. So I came up to an idea of building my own logging 
system for my requirements and maybe others too. So I started to build this 
thing.

## `Logging` class

### Severity levels
A simple enum named `klog::level` where I named up-to 6 levels of severity, viz.
- `TRACE`   For the trace messages, these should be more often than anything.
- `DEBUG`   For the debug messages where you tell something happened.
- `INFO`    If anything happened and to be notified to the user.
- `WARN`    Warn the user if anything goes wrong in the program, which is 
  not too harm to the system or program
- `ERROR`   Any exceptions from the program that can crash the program or 
  system
- `FATAL`   If a Fatal log comes, that means the complete system crashes 
  and the data maybe corrupted. If this happens the program maybe even destroyed

You are not needed to write the full name of the level like `klog::level::INFO`,
for every level, there is a #define directive is used to directly access 
them like `INFO`.

### inbuilt logger `LOG`
There is a static Logging object already defined in the header file, named `LOG`
which can be directly used like `LOG() << "hi"`, the syntax and brief usages 
are specified below. The reason behind this implementation is it resembles 
the standard `cout` stream in the c++, so this is a log stream which 
internally uses the `cout` itself this is due to the fact that you can 
directly print other objects like `Point(4, 5)` to the console when you just 
like your standard output stream where you may overload the `operator<<` to 
print objects to the console. So that way you can directly print objects to 
the log stream without overloading `operator<<` again for this logger.
```cpp
// Somewhere I overloaded the << to print the Point object to standard output. 
std::ostream &operator(std::ostream &stream) {
    std::cout << "(" << p.x << ", " << y << ")" << '\n';
    return stream;
}
...

LOG(INFO) << "Igniting the server socket." << klog::endl;
Point p(4, 5);
LOG(TRACE) << "Created a point object : " << p;
// Here I can directly use that implementation without overloading again.
```

## syntax and using a logger
This implementation idea is actually a syntax copy from the `glog` by google,
But I swear no code is copied from `glog`, also it took me days to even 
spectate the `glog` lib.  
The syntax is simple, We will specify the min level of log messages to log 
onto the console with the `set_log_level(level)` method. Saying this, all 
messages above the severity level more than specified level will be written 
onto the console. We will specify the severity of each message with normal 
braces `(level)`. This looks like this : `LOG(INFO)` this will specify the 
severity level of this message after this with the `<<` operator. Use `<<` 
to chain your message to the log message. You can chain as many messages or 
strings with `<<` as you wish to the log message line.  
Always try to end the line with `klog::endl`, this is also an analogy to the 
standard `cout` formatting and flushing. Use this rather than using `std::endl`
or `'\n'` which can also be used, as this way is more efficient and helpful 
in the thread safety and synchronization.

```cpp
LOG(INFO) << "Firing the server." << klog::endl;
LOG(WARN) << "Cannot fire the server." << klog::endl;
LOG(TRACE) << "Initialized a client thread" << '\n';
// '\n' can also be used, but this decreases the thread safety efficiency.
```

> Using the `klog::endl` makes the logger very efficient at working in 
> thread safety conditions and also more performance efficient  than the normal 
> `std::endl`, which can also be used without any issue.



