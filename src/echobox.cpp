#include <iostream>
#include <string.h>
#include <editline/readline.h>

void initialize_editline();
char **completion_callback(const char *text, int start, int end);
char * match_generator(const char *text, int state);

int main(int argc, char *argv[])
{
    char *line;
    bool running = true;
    
    initialize_editline();

    while (running)
    {
        line = readline("Prompt: ");

        if (!line)
        {
            break;
        }

        printf("you typed: %s\n", line);


    }


    return 0;
}

void initialize_editline()
{
    rl_attempted_completion_function = completion_callback;

}

char **completion_callback(const char *text, int start, int end)
{
    char **matches;
    matches = nullptr;

    if (start == 0)
    {
        matches = completion_matches(const_cast<char *>(text), match_generator);
    }

    return matches;
}

char * match_generator(const char *text, int state)
{
    char *match, *commandName;
    static const char *commandList[5] = {"hello", "howdy", "howareya", "hi", nullptr};
    static int listIndex = 0, len = 0;

    if (state == 0)
    {// initial state, so initialize list of things
        listIndex = 0;
        len = strlen(text);
    }

    while ((commandName = const_cast<char *>(commandList[listIndex])))
    {
        listIndex++;
        if (strncmp (commandName, text, len) == 0)
        { // found a match, return a malloc'd duplicate
            match = static_cast<char *>(malloc(strlen(commandName)));
            strcpy(match, commandName);
            return match;
        }
    }

    return nullptr;
}

    
