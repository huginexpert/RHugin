\name{propagate}
\alias{propagate}

\title{Propagation}

\description{
Establish the specified equilibrium using the evidence mode indicated for the incorporation of evidence on all junction trees in the domain. Additionally, revised beliefs are computed for all the nodes in the domain.
}

\usage{
propagate(domain, equilibrium = c("sum", "max"), mode = c("normal", "fast"))
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{equilibrium}{a character vector of length one specifying the equilibrium method.}
  \item{mode}{a character vector of length one specifying the evidence mode.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{initialize.domain}}.
}

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


