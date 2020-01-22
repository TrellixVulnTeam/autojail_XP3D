# Autmated Jailhouse configuration

## Getting Started

To install the package in development mode:

    pip install poetry
    git submodule update --init --recursive
	poetry shell
	
	
Then copy external/automate/automate.yml to ~/.automate and adopt the 
configuration to your needs. Metadata should point to the absolute path
of the directory metadata inside external/automate. 

## Commandline interface

TODO: Interface of commandline generator 

Check out jailhouse:

     automate-run update
	 
Build jailhouse for all boards:

     automate-run build 
	 
Build jailhouse for a specific board:

    automate-run build -b jetsontx2
	
Deploy jailhouse:

    automate-run deploy
	
Deploy jailhouse for a specific board:

    automate-run deploy -b jetsontx2
