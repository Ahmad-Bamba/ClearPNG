# Stub: NOT FINAL

# Contributing to ClearPNG

First off, thanks for taking the time to contribute!

All types of contributions are encouraged and valued. See the [Table of Contents](#table-of-contents) for different ways to help and details about how this project handles them. Please make sure to read the relevant section before making your contribution. It will make it a lot easier for us maintainers and smooth out the experience for all involved. The community looks forward to your contributions. 🎉


## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [I Have a Question](#i-have-a-question)
- [I Want To Contribute](#i-want-to-contribute)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Enhancements](#suggesting-enhancements)
- [Your First Code Contribution](#your-first-code-contribution)
- [Improving The Documentation](#improving-the-documentation)
- [Styleguides](#styleguides)
- [Commit Messages](#commit-messages)


## Code of Conduct

This project and everyone participating in it is governed by the
[CONTRIBUTING.md Code of Conduct](blob/master/CODE_OF_CONDUCT.md).
By participating, you are expected to uphold this code. Please report unacceptable behavior
to <>.


## I Have a Question

> If you want to ask a question, we assume that you have read the available [Documentation]().

Before you ask a question, it is best to search for existing [Issues](/issues) that might help you. In case you have found a suitable issue and still need clarification, you can write your question in this issue. It is also advisable to search the internet for answers first.

If you then still feel the need to ask a question and need clarification, we recommend the following:

- Open an [Issue](/issues/new).
- Provide as much context as you can about what you're running into.
- Provide project and platform versions (nodejs, npm, etc), depending on what seems relevant.

We will then take care of the issue as soon as possible.



## I Want To Contribute

> ### Legal Notice 
> When contributing to this project, you must agree that you have authored 100% of the content, that you have the necessary rights to the content and that the content you contribute may be provided under the project license.

### Reporting Bugs


#### Before Submitting a Bug Report

A good bug report shouldn't leave others needing to chase you up for more information. Therefore, we ask you to investigate carefully, collect information and describe the issue in detail in your report. Please complete the following steps in advance to help us fix any potential bug as fast as possible.

- Make sure that you are using the latest version.
- Determine if your bug is really a bug and not an error on your side e.g. using incompatible environment components/versions (Make sure that you have read the [documentation](). If you are looking for support, you might want to check [this section](#i-have-a-question)).
- To see if other users have experienced (and potentially already solved) the same issue you are having, check if there is not already a bug report existing for your bug or error in the [bug tracker](issues?q=label%3Abug).
- Also make sure to search the internet (including Stack Overflow) to see if users outside of the GitHub community have discussed the issue.
- Collect information about the bug:
- Stack trace (Traceback)
- OS, Platform and Version (Windows, Linux, macOS, x86, ARM)
- Version of the interpreter, compiler, SDK, runtime environment, package manager, depending on what seems relevant.
- Possibly your input and the output
- Can you reliably reproduce the issue? And can you also reproduce it with older versions?


#### How Do I Submit a Good Bug Report?

> You must never report security related issues, vulnerabilities or bugs including sensitive information to the issue tracker, or elsewhere in public. Instead sensitive bugs must be sent by email to <>.


We use GitHub issues to track bugs and errors. If you run into an issue with the project:

- Open an [Issue](/issues/new). (Since we can't be sure at this point whether it is a bug or not, we ask you not to talk about a bug yet and not to label the issue.)
- Explain the behavior you would expect and the actual behavior.
- Please provide as much context as possible and describe the *reproduction steps* that someone else can follow to recreate the issue on their own. This usually includes your code. For good bug reports you should isolate the problem and create a reduced test case.
- Provide the information you collected in the previous section.

Once it's filed:

- The project team will label the issue accordingly.
- A team member will try to reproduce the issue with your provided steps. If there are no reproduction steps or no obvious way to reproduce the issue, the team will ask you for those steps and mark the issue as `needs-repro`. Bugs with the `needs-repro` tag will not be addressed until they are reproduced.
- If the team is able to reproduce the issue, it will be marked `needs-fix`, as well as possibly other tags (such as `critical`), and the issue will be left to be [implemented by someone](#your-first-code-contribution).




### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for CONTRIBUTING.md, **including completely new features and minor improvements to existing functionality**. Following these guidelines will help maintainers and the community to understand your suggestion and find related suggestions.


#### Before Submitting an Enhancement

- Make sure that you are using the latest version.
- Read the [documentation]() carefully and find out if the functionality is already covered, maybe by an individual configuration.
- Perform a [search](/issues) to see if the enhancement has already been suggested. If it has, add a comment to the existing issue instead of opening a new one.
- Find out whether your idea fits with the scope and aims of the project. It's up to you to make a strong case to convince the project's developers of the merits of this feature. Keep in mind that we want features that will be useful to the majority of our users and not just a small subset. If you're just targeting a minority of users, consider writing an add-on/plugin library.


#### How Do I Submit a Good Enhancement Suggestion?

Enhancement suggestions are tracked as [GitHub issues](/issues).

- Use a **clear and descriptive title** for the issue to identify the suggestion.
- Provide a **step-by-step description of the suggested enhancement** in as many details as possible.
- **Describe the current behavior** and **explain which behavior you expected to see instead** and why. At this point you can also tell which alternatives do not work for you.
- You may want to **include screenshots and animated GIFs** which help you demonstrate the steps or point out the part which the suggestion is related to. You can use [this tool](https://www.cockos.com/licecap/) to record GIFs on macOS and Windows, and [this tool](https://github.com/colinkeenan/silentcast) or [this tool](https://github.com/GNOME/byzanz) on Linux. 
- **Explain why this enhancement would be useful** to most CONTRIBUTING.md users. You may also want to point out the other projects that solved it better and which could serve as inspiration.



### Your First Code Contribution
TODO: getting a build environment set up.

### Use of synthetic code generators
Use of synthetic code generators (also known as "AI" co-pilots) such as ChatGPT and GitHub Co-Pilot is strictly prohibited.
If you are found to have written a contribution with these tools, this will be considered a breach of trust.
Synthetic code generators are simultaneously [not reliable](https://www.businessinsider.com/chatgpt-frequently-wrong-about-coding-but-sounds-smart-2023-8) and persuasive when wrong.
They are also created through theft of code examples without the authors' consents.

While this is a small project I am maintaining on my own time, I do want the quality of code to be production-level.
Honestly, if you're not good enough to debug or write software on your own, you are not good enough to be contributing to open-source software period.

### Improving The Documentation


## Styleguides

### Commit Messages

The commit messages do not need to follow any particular format as long as they are descriptive. 

### Pull requests
For a pull request to be accepted, the patch must compile the project with the following CMake options and the generator of your choice:
```
mkdir build
cd build
cmake ../ -DWITH_CLANG_FORMAT:BOOL=ON -DWITH_CLANG_TIDY:BOOL=ON -G"Unix Makefiles"
make
```

In addition, all currently existing unit tests must pass. Specifically:
```
mkdir build
cd build
cmake ../ -DWITH_CLANG_FORMAT:BOOL=ON -DWITH_CLANG_TIDY:BOOL=ON -G"Unix Makefiles"
make
ctest -v
```

should return no errors.

If you are fixing a bug, you must create a unit test case that shows this bug is now resolved, and that unit test must pass.

You are free to write your contribution in whatever format you wish.
The CMake options `-DWITH_CLANG_FORMAT:BOOL=ON -DWITH_CLANG_TIDY:BOOL=ON` automatically format your code with `clang-format`.
The projecet also automatically treatas all compiler warnings as errors.
Your changes should compile successfully with these settings for `g++` on Linux, `clang++` on Windows and Linux, and `MVSC` on Windows.
TODO: CI/CD pipeline to enforce this.

If you have the time, compiling with `-DTIDY_EXTRA:BOOL=ON` and addressing those waranings is appreciated.
It will not be, however, necessary for a PR approval.

Pull requests must refer back to an open issue. 
If you would like to suggest a change, make the issue first before working on it.

#### Branch naming
Branches should be named `bugfix/xxx` for bug fixes, `docs/xxx` for clarifications to the documentation or `feature/xxx` for new features, where `xxx` is the issue number on GitHub.

## Attribution
This guide is based on the **contributing.md**. [Make your own](https://contributing.md/)!
