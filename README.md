# RHugin

RHugin is a middleware built to enable R developers to use the HUGIN API from any R program.

## Installation
### Hugin Developer and Researcher
The newest version of RHugin is now on github instead of r-forge.
To install the package run: 
`devtools::install_github("huginexpert/rhugin")`

The master branch should also work for other versions of Hugin.

### Hugin Lite
To install the package run: 
`devtools::install_github("huginexpert/rhugin@Hugin_lite")`

### Dependencies
Make sure to install to have installed devtools and rtools.
devtools can be installed by running the command `install.packages("devtools")`.
rtools is installed from this website [link](https://cran.r-project.org/bin/windows/Rtools/)

It may be required to install the package Rgraphviz by running: 
`install.packages("BiocManager")` and
`BiocManager::install("Rgraphviz")`

### Not supported
The Hugin versions Education and Explorer can not be used with RHugin.

## Activating the library

After installing **RHugin**, you need to load the library in your R session so that its functions become available.

Run the following command to activate it:

```r
library(RHugin)
```

## Who Maintains RHugin ?
RHugin is currently maintained by Hugin Expert.
Please visit your website [here](http://www.hugin.com).

## Who Started developing RHugin ?
RHugin was initiated by Kjell Konis (kjellpk) at his [GitHub](https://github.com/kjellpk/RHugin).

## How To Get Help?

For assistance with the RHugin package please contact support@hugin.com
