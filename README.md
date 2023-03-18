# WHAT IS THIS?
A simple, CLI password manager that generates a strong password and stores it in a text file.
This only works on Linux systems.

## SETUP
1. Clone this repo.

```git clone https://github.com/cincodemayo11/password-manager.git```

2. Navigate (`cd`) into the repo folder.

```cd password-manager```

3. Run the passman installer by running:

```sudo ./install```

## HOW TO USE


### To generate and store a new password, run:

```passman w sitename passwordlength```

e.g. `passman w facebook 11` will generate a strong password 11 characters long, and will be stored under the name "facebook".

*Note* - You may need to use your root privileges to write a password, i.e.;

```sudo passman w sitename passwordlength```



### To check an existing password, run:

```passman r sitename```

e.g. `passman r facebook` will display the password stored under the name "facebook".

*Note* - You may need to use your root privileges to read a password, i.e.;

```sudo passman r sitename```



### To delete an existing password, run:

```passman x sitename```

e.g. `passman x facebook` will delete the password stored under the name "facebook".

Note* - You may need to use your root privileges to delete a password, i.e.;

```sudo passman x sitename```



Feel free to report any issues or ask any questions.

*God bless all frogs and may they roam and croak the Earth*