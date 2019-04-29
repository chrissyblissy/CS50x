# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

pneumonoultramicroscopicsilicovolcanoconiosis is a pneumoconiosis caused by inhalation of very fine silicate or quartz dust.


## According to its man page, what does `getrusage` do?

it returns the resource usage statistics.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because passing the reference is much quicker and uses less memory than passing a large struct.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop iterates over each character, checking if they are a letter. If it is too long or has characters that are not alphabetical then it iterates over them but then ignores them. If they are alphabetical it appends them to the string word[]. If the word is spelt correctly then check returns ‘true’ so the Boolean, misspelled, will give ‘false’ so the word will not be printed.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

As this means each character is checked individually, whereas fscanf takes in any characters until it reaches white space which means it would include punctuation as part of a word.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Because while they are being checked we don't want any function to change the value contained in them.