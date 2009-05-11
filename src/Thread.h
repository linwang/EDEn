#ifndef __THREAD_H_
#define __THREAD_H_

/**
 * A Thread is, in this case, an object that can yield, resume or block.
 * The typical scenario for a Thread object is a resumption (with the amount of
 * time since the last frame passed in), followed by blocking or by destruction.
 *
 * Thread objects do not actually use "threads" in the typical sense. They are
 * semi-coroutines, running serially, resuming and suspending.
 * They do not have their own threads of execution.
 *
 * @author Noam Chitayat
 */
class Thread
{  /** 
    * The next available thread ID to use for constructing a thread.
    */
   static int nextThreadId;

   protected:
      /** The numeric identified of this thread (currently just used for debugging) */
      int threadId;

   public:
      
      /**
       * Constructor. Initializes the thread ID.
       */
      Thread();
   
      /**
       * @return the numeric identifier for this Thread.
       */
      int getId();

      /**
       * Resume this Thread, or run through its logic.
       *
       * @param timePassed The amount of time that has passed since the last frame
       *                   (roughly speaking, since the last run of this Thread)
       *
       * @return true iff the Thread has run to completion, false if it has
       *              yielded or encountered an error.
       */
      virtual bool resume(long timePassed) = 0;
};

#endif
