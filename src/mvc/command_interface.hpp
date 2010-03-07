#ifndef _COMMAND_INTERFACE_HPP_
#define _COMMAND_INTERFACE_HPP_


/**
 * Abstract Command
 */
class CommandInterface { 

public:

  virtual ~CommandInterface() {}

  /**
   * Do your job. It should be possible to 
   * undo the job by calling 'undo'.
   */
  virtual void execute() = 0;

  /**
   * Undo the job previously done by 'execute'.
   */
  virtual void undo() = 0;
  
};

#endif // _COMMAND_INTERFACE_HPP_
