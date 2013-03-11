\name{RHugin}
\alias{RHugin}

\title{
The RHugin Package
}

\description{
The RHugin package provides an R interface for the Hugin Decision Engine (HDE). RHugin supports building and making inference from Bayesian belief networks and influence diagrams, learning network structure, and learning conditional probability tables. All the functions in the RHugin package are documented. A complete list of functions can be obtained using the command \code{ls(pos = "package:RHugin")}. The documentation for each function can be accessed using \code{?} or the \code{help} function. The package also contains several demos; see \code{demo(package = "RHugin")} for a list.
}

\details{
The RHugin package attempts to make working with the Hugin Decision Engine (HDE) as R-like as possible. However, there are two important caveats:

1) an RHugin domain is an eternal pointer. The value of the external pointer is a connection to a Hugin domain in the Hugin Decision Engine. A copy of an eternal pointer contains the same value as the original and thus is a connection to the same Hugin domain in the HDE as the original. An example is given below. As a best practice, do not copy Hugin domains using the R assignment operators \code{<-} and \code{=}.

2) Hugin domains are external to R and cannot be saved in an R workspace. The functions \code{read.rhd} and \code{write.rhd} are provided for loading and saving Hugin domains. Any domains not saved when quitting R will be lost.
}

\references{
The RHugin Project website: \url{http://rhugin.r-forge.r-project.org}

HUGIN EXPERT website: \url{http://www.hugin.com}

HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# This example is provided to demonstrate why RHugin domain objects #
# should not be assigned using the <- and = operators.              #

# Create an empty domain
hd.one <- hugin.domain()

# Make a copy of the external pointer hd.one
hd.two <- hd.one

# Add a node using the copy
add.node(hd.two, name = "hello")

# Since both hd.one and hd.two reference the same domain in the HDE,
# accessing the domain using hd.one shows the added node
hd.one
}

\keyword{programming}


