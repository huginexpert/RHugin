\name{RHugin}
\alias{RHugin}

\title{
The RHugin Package
}

\description{
The RHugin package provides an interface to the Hugin Decision Engine (HDE) so that it can be controlled from within the R environment.  Users are able to build and make inference from Bayesian belief networks (including those with continuous Gaussian nodes) and influence diagrams, learn network structure and learn conditional probability tables.  All of the functions in the RHugin package are documented.  A complete list of functions can be obtained using the command \code{ls(pos = "package:RHugin")} and the documentation for each listed function can be accessed using \code{?function}.  The package also contains several demos: \code{demo(package = "RHugin")} will display the available demonstration scripts.
}

\details{
The RHugin package attempts to make working with the Hugin Decision Engine as R-like as possible. However, there are two important caveats that users should be aware of.

The first is that an RHugin domain, the object that RHugin uses to represent a domain in the HDE, is a special type of R object called an eternal pointer.  The value of the external pointer points to the actual domain in the HDE.  The consequence of this arrangement is that a copy of an eternal pointer contains the same value as the original and hence still points to the same domain the in the HDE.  An example is given below.  As a best practice, it is recommended that users not copy Hugin domains using the R assignment operators \code{<-} and \code{=}.

The second caveat is that, since the actual Hugin domain exists in the HDE (and not in R), it cannot be saved in an R workspace and therefore is lost when quitting R.  The functions \code{read.rhd} and \code{write.rhd} are provided for loading and saving Hugin domains.  Note that \code{write.rhd} must be called before quitting R if the domain is to be saved.
}

\references{
The RHugin Project website: \url{http://rhugin.r-forge.r-project.org}

HUGIN EXPERT website: \url{http://www.hugin.com}

HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}
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


