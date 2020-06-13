The final project of 2020-1 OSS Lab in Handong Global University
=============================================
### Project name : The contact application of professors in CSEE, HGU
### Video URL : 


## What does this project do?
This application provides management to **emails and contact information** of **professors in CSEE, HGU**.
* Adding : You can load the data from the txt file, or insert by your input.
* Deleting : You can delete a contact from the application by entering name or email.
* Retrieving : You can search a contact from the application by entering name or email.
* Saving : You can save the data in application into a file.
	* Note : If you enter a filename already exists, the original file will be deleted!!
* Printing : You can print the data in application.

## Why is this project useful?
It is hard job to search HGU web site to know the email or phone-number of the professor every time when you want to contact the professor.
So I thought that it would be really useful to have the program that could store contacts.

And I was working on my homework of Data structures about contacts application. 
At that time, I thought that 
“How about upgrading this application into an application that lets you change and save the contacts of professor?”
And “How about applying it to raspberry pi?”

This is the story dealing with how this application was created.
So that, you can manage the contacts in it, and save the changes into a file.
Later, when you want to contact the professor or modify the contacts, this application will give you the great help!

## How do I get started? (+Tool)
1. The source code of this application was written in **C++**, so you have to install **g++** in your raspberry pi.
```
	$ sudo apt-get install g++
```
2. Enter "make" command to compile.
```
	$ make
```
3. There will be an executable file "contactAPP".
Enjoy!
```
	$ ./contactAPP

```
## Where can I get mor help, if I need it?
When you need some help, please email me 21600621@handong.edu.

Thank you for visiting!!