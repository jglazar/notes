# Codecademy git/GitHub course

## basics

*working directory* --> `git add` --> *staging area* --> `git commit` --> *repo*  

* `git init`  --  start project and create .git directory  
* `git diff <name>`  --  check changes between working dir and staging area versions  
* `git status`  --  show all files that are different between working dir and staging area  
note that `git commit` requires a message, which can be specified in quotes using `-m "<message>"` 
....note should be <50 characters and written in present tense (e.g., "add feature")  
* `git log`  --  show chronological list of commits with SHA id, author, date/time, and message  
* `git show HEAD`  -- show current commit  
* `git checkout HEAD <filename>`  --  copy file version from HEAD commit into working dir  
* `git reset HEAD <filename>`  --  copy file version from HEAD commit into staging area.  
....unstages file, leaving working dir version alone  
* `git reset <SHA>`  --  set HEAD to that commit  
....only need 1st 7 characters of SHA  
....does this delete further-out commits?
....can copy these files into working directory with `git checkout HEAD <filename>`

## other useful commands

* `git stash`  --  temporarily store data without commit. useful for hopping branches  
* `git log` options  
  * `oneline`  --  summarize commits with one line each  
  * `-S <keyword>`  --  search for keyword in commit messages  
  * `--graph`  --  display graph for branches  
* `git commit --amend`  --  overwrite HEAD, which is useful for fixing minor mistakes  
  * `--no-edit` keeps original commit message  
  * may need to use `git push -f` to force update on remote repo
* `git config -- global alias.<shorthand> "<git command>"`  --  define shorthand for git command  
* `git --version`  --  display current git version  

## GitHub

1. create local git project
2. create new repo on GitHub with no presets (can create issues with first commits)
3. push existing repo from command line to GitHub
  1. `git remote add origin <URL>` (origin = original project repo)
  2. `git branch -M main`
  3. `git push -u origin main`

git username =/= GitHub username, necessarily!  
* `git config --global user.name "<name>"`  --  sets username  
* `git config --global user.name`  --  checks username  
can similarly set git email address  

* `git remote add origin <URL>`  --  sets remote repo  
* `git push`  --  push local main branch to remote repo  

### collaboration

1. create branch
2. commit changes
3. create pull request
4. review pull request
5. merge + delete branch


## markdown

language between plaintext and HTML  
useful for GitHub README files  
`#`  --  heading  
`##` --  subheading  
`*`  --  italics  
`**` --  bold  
`~`  --  strikethrough  
`*/+/-`  --  unordered list  
`1/2/3`  --  ordered list  
`>`  --  separate quote  
can add images and GIFs

## branching

* `git branch`  --  check current branch  
* `git branch <name>`  --  create new branch  
* `git checkout <name>`  --  switch to branch  
* `git merge <name>`  --  merge current branch with target branch  
  * fast-forward is when target branch is strictly newer than current branch  
* "merge conflict"  --   same line of code has different versions in each branch  
  * git will edit file to highlight conflicts  
  * need to edit file and remove git's formatting, then re-try merge  
* `git branch -d <name>`  --  delete branch  

## remote

git remote is a shared repo for multiple collaborators  
* `git clone <remote-location> <clone-name>`  --  create clone locally  
  * usually just of main branch, must manually checkout/pull other branches  

remote location will be nicknamed "origin"  
* `git remote -v`  --  list all remotes for project. lists fetch and pull copies  
* `git fetch`  --  find changes on origin and put into "origin/main" branch  
* `git merge origin/main`  --  merge remote with local main branch (if in local main branch)  
* `git remote add upstream <URL>`  --  allows collecting new updates with:  
* `git fetch upstream`  --  grab updates from upstream defined above  

local project workflow:  

1. fetch and merge remote
2. create new branch
3. develop and commit
4. fetch and merge remote again
5. push for review

* `git push origin <branch-name>`  --  offer to merge branch with origin's main  

*pull requests are requests to merge your repo's branch with another repo's branch  
  * keep title concise  
  * address what, why, and how in body  
  * ensure branch has clear commits  
  * add code comments  
  * keep pull requests small  

big project workflow:  

1. fork repo on GitHub
2. `git clone <URL>`
3. cd into directory
4. `git branch <name>` and `git checkout <name>` to create new branch
5. edit and commit in branch
6. `git push` (after setting upstream)
7. "compare and pull request" on your GitHub fork

## rebase

* `git rebase`  --  move base of branch, like a re-do  
keeps git commit history cleaner than multiple `git pull origin main` (or merge) commands  
re-applies commits of new base branch  
merge preserves history, rebase overwrites history  
merge adds branch's changes to main, rebase adds main's changes to branch  
only use locally! don't rebase after pushing!  
use rebase often and collect changes in one commit

## gitignore

`.gitignore` file specifies files/directories/patterns to leave out of staging  
best to ignore:  
* config files 
* compiled binaries
* build directories
* log files
* dependencies from package manager
* system files like `.DS_Store`
can add comments with `#`  
patterns include `*`, `!` (negate ignore), `[a-z]`, `[A-Z]`, `[0-9]`, `**` (directories)  
GitHub includes some templates for different languages  

## extras

GitHub Pages helps you host web pages and automatically update  
GitHub can integrate 3rd-party tools like Slack  
GitHub Project Management provides dashboards for issues and pull requests  
GitHub Issues tracks bugs  
....can use labels like "bug" and "feature" to help organize  

### GitHub Actions
GitHub Actions sets automatic triggers  
found in `.github/workflows/` directory  
`unittests.yaml`  --  define unit testing with each push/pull request  

### GitHub command line interface  
access and modify issues and pull requests  
* `gh auth login`  --  log in  
* `gh issue create --title "<title>" --body "<body>"`  --  create issue  
* `gh issue status`  --  track issue  
* `gh pr create`  --  submit pull request  
  * mention issue number with "#[id]"  
* `gh pr merge`  --  accept pull request  
