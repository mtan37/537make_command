//parses the Make file.
//It will read the file and load it into a struct called Target
//Target... just like the name, represents a target file. It will have three fields
    //1)fileName
    //2)a list of dependencies
    //3)a list of command to execute
    //4)indicte whether it is out of date
//it will store those loaded targets into a list of targets.
//it will call the validator to check:
    //1)whether there is a chain in the dependencies. If there is, not more check is needed and return error
    //2)whether the dependecies are all existing files or targets
    //3) whether the dependencies are out of date
//a target will be only sent to the executor if it is out of date
 
