# Prompt engineering

## Prompts

LLMs use context from earlier questions to answer prompts
  * E.g., tone, level of detail
  * Can prespecify "from now on, suggest a better version of my question"
  * LLMs can prompt us back by asking questions

ChatGPT has info up to Sept 2021. Can augment with our own data via prompt

LLMs regurtitate frequently-seen patterns
  * E.g., "Mary had a little..." --> "lamb whose fleece was white..." vs. "Mary
    had a microscopic..." --> "friend named Max who..."
  * Weaker patterns lead to more variance in possible continuations
  * Words can even be patterns. "Microscopic" has scientific connotation

Be specific with prompt to ensure less variance
  * "With respect to" is a useful phrase
  * Style/tone of our prompt influences style/tone of output

You can program how the LLM outputs data
  * E.g., "Convert my input into CSV format"

## Useful patterns

Persona -- ask LLM to pretend to be an expert in the field
  * E.g., "Pretend you're a skeptical computer scientist"
  * You can even ask it to act as a hacked Linux terminal
  * Use different perspectives for a more complete answer
    * E.g., CFO, head of network security, head of HR, ...
  * Persona is very information-dense for LLM instruction
  * "Act as an X. I will provide you Y. Tell me Z."

Give LLM custom info -- just copy/paste into prompt
  * Be sure to state important assumptions
  * There is a limit on the amount of text passed in 1 prompt
    * Can ask LLM to compress info one chunk at a time

Use the conversation as a large prompt
  * Each question builds off the last to solve a big problem
  * "I'm not sure about blank. What would you do?"
  * "I'm getting lost. Summarize the main topics we've covered"
  * Some conversation paths will reach a dead end. Explore many questions

Root prompts set ground rules. Typically, things that'll always or never be done
  * E.g., never use offensive language and always suggest the cheapest option
  * Can have LLM pretend its training cuts off earlier than it truly does

Use the LLM to refine the question
  * "Whenever I ask a question, propose a better question"

Cognitive verifier -- ask LLM to subdivide questions into smaller questions
  * "When asked a question, generate more sub-questions then combine the answers
    to produce a final answer"
  * Can tell it to ask you to specify certain parameters (budget, e.g.)

Audience persona -- tell LLM to instruct a type of person
  * "Assume you're talking to an -adjective- -noun-"

Flipped interactions -- tell the LLM to ask you questions to solve a problem
  * "Ask me questions about blank until you have enough info to do blank for me"

Few-shot examples -- show the LLM how to do a task w example inputs and outputs
  * "Here are some examples: input - '...' output - '...'"
  * Can use this method to teach actions and reactions
  * Can use a LLM to generate examples, which we can edit/provide answers to
  * Can build complex scenarios with intermediate actions and reasoning
    * Input - thought - action - reason is good format. Can repeat thought -
      action - response to continue hypothetical situation
  * Don't just say "Input: ..., Output: ...." Use more specific nouns like
    "Situation: ..., Reaction: ..."
  * Stick with a clear pattern and cohesive theme behind your inputs and outputs
  * Include enough context that 10 humans could come to the same answer
    * Can include rules to better specify task

Chain of thought prompting -- ask the LLM for its rationale
  * Can combine with few-shot examples. Give questions and answers w reasoning.
    Give reasons before answers, teaching LLM to think before answering

ReAct -- teach LLM to think about seeking answers elsewhere
  * Augment chain of thought examples with ideas of where to get info
    * Task - think - action - result - think - action - result - ...
    * Some actions should include "search" keyword
  * LLM can infer patterns in URLs to find most relevant websites

Use LLMs to grade each other
  * Just show the grader how to grade using example answers, corrections, and a
    final grade

Gameplay -- have the LLM create a game to play with you to hone your skills
  * "Let's play a game. You challenge me to generate a prompt to accomplish a
    goal, I give a prompt, you evaluate it, and you tell me how well I did."
  * Be sure to use the good prompt engineering tools provided above

Specify a template for the LLM's responses
  * "I'll provide a template. ALL-CAPS words are placeholders. Preserve overall
    formatting"
  * ChatGPT understands markdown formatting
  * Can place complex instructions in placeholder slots. E.g., `"***Summary***
    <one paragraph summary>"`

Meta language creation -- use your own shorthand with the LLM
  * Use a few examples to teach ChatGPT your shorthand

Recipe pattern asks LLM to fill the gaps between start and finish states
  * Useful alongside custom meta language. Can use "..." to indicate places for
    the LLM to fill in blanks

Ask LLM to create alternative approaches too
  * "If there are alternative solutions, list them and ask me which to pick"
  * Can also ask to compare/contrast options

Ask LLM to create prompts for itself
  * Make sure to proofread. LLM can make mistakes in its prompt
  * Works well with alternative approaches method

At end of prompt, specify for the LLM to wait for you to make the first move
  * Prevents LLM from generating irrelevant information

For large tasks, ask for an outline first
  * This circumvents built-in output length limits
  * Ask the LLM to act as an "outline expander." Only expand points of interest
  * Want standalone self-contained units that fit together well

Use menu actions to avoid repeating long patterns
  * Basically, meta language for acting on outlines or other large structures

Fact checklists list all found facts at the end of the output for verification
  * "Whenever you output, generate a set of fundamental facts that could
    undermine your veracity if any are incorrect. List these at the end"
  * Check facts against original text or external sources

Tail generation reminds the LLM of previously established rules
  * "... When you are done, ask me for the next -prompt with rules-"

Semantic filters removes/retains info in original text
  * E.g., remove all dates and condense this text

# ChatGPT data analysis

Advanced data analysis tool (formerly Code Interpreter, hereafter ADAT)
can read documents and summarize using statistics and graphs

Can start with just data, and iterate through visualization, analysis, 
explanations, and extensions
  * E.g., upload recipe to create grocery list, estimate calories/macros, ...

Have ADAT ask you questions about your goals

ADAT has no internet access and limited toolkit. Has short memory and needs
everything specified in single conversation
  * Break projects into chunks and provide feedback

Can treat documents as objects (to be acted upon) or knowledge (to be
analyzed and interpreted)
  * ADAT will handle interpretation tasks. Will generate Python for others

ADAT can solve rule-heavy tasks ChatGPT would fail, like Wordle
  * ChatGPT can even hallucinate new data

ADAT can read document, identify missing details and re-read, break down
questions contained within, follow instructions within, and explore
hypotheticals

ADAT can figure out data structure, verify consistency

Can analyze media like videos, audio, and images
  * Find and display specific video frames, resize and transform images, create
    gifs, create powerpoints, generate metadata

Pipelines offer straightforward ways to accomplish complex tasks
  * E.g., turn video into blog post by loading transcript, identifying tone and
    concepts, drafting post outline, and filling in and polishing
  * Can iterate through plan ideas

Split large documents into chunks. Can implement a search method

Handle large outputs step-by-step. Save and combine incremental outputs

10 best practices
  * Save intermediate files to prevent loss of progress
  * Plan step-by-step to enhance repeatability
  * Use mementos where ADAT lists out the plan, current step, and progress
  * Have ADAT read and explain all documents and data in several ways
  * Implement error detection to prevent hallucinations going unnoticed
  * Have ADAT try alternate approaches 
  * Be explicit about goals, requirements, and constraints
  * Edit the conversation when errors occur to avoid error propagation
  * Tell ADAT to analyze without Python when needed
