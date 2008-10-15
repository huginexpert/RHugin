\name{propagate}
\alias{propagate}

\title{Propagation}

\description{
Establish the specified equilibrium using the evidence mode indicated for the incorporation of evidence on all junction trees in the domain.  Additionally, revised beliefs are computed for all the nodes in the domain.
}

\usage{
propagate(domain, equilibrium = c("sum", "max"), mode = c("normal", "fast"))
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{equilibrium}{a character string specifying the equilibrium method.}
  \item{mode}{a character string specifying the evidence mode.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_domain_propagate}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Select states
set.finding(AppleTree, "Loses", "yes")

# Propagate and get beliefs
propagate(AppleTree)
get.belief(AppleTree, "Sick")
}

\keyword{programming}


