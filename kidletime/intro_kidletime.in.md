# Detect and Handle System Idling

KIdleTime is a helper framework to get reporting information on idle time of the system. It is useful not only for finding out about the current idle time of the system, but also for getting
notified upon idle time events, such as custom timeouts or user activity. It features:

* current idling time
* timeout notifications, to be emitted if the system idled for a specified time
* activity notifications, if the user resumes acting after an idling periode

## Using It

For understanding how to use KIdleTime, we create a small testing application, called KIdleTest. This application initially waits for the first user action and afterwards registers some timeout intervals, and acts whenever the system idles for such a time. The KIdleTime framework provides a singleton KIdleTime, which provides us with all necessary signals and information about the idling status of the system. For our example, we start with connecting to the signals for user resuming from idling and for reaching timeouts that we will set ourselves:

@@snippet(kidletime/examples/KIdleTest.cpp, initialize, cpp)

We also tell KIdleTime to notify us the very next time when the user acts. Note that this is actually only for the next time. If we were interested in further events, we had to invoke `catchNextResumeEvent()` again. Next, in our event listener for the user resume event, we add register a couple of idle intervals:

@@snippet(kidletime/examples/KIdleTest.cpp, resumeEvent, cpp)

If any of these idle intervals is reached, our initially registered `timeoutReached(...)` slot is invoked and we print out an appropriate message.

@@snippet(kidletime/examples/KIdleTest.cpp, timeoutReached, cpp)

From there on, depending on the reached idle interval, we go back to one of the former steps.
