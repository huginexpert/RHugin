\name{propagate.RHuginDomain}
\alias{propagate}
\alias{propagate.RHuginDomain}

\title{Propagation}

\description{
Establish the specified equilibrium using the evidence mode indicated for the incorporation of evidence on all junction trees in the domain.  Additionally, revised beliefs are computed for all the nodes in the domain.
}

\usage{
propagate(object, ...)
\method{propagate}{RHuginDomain}(object, equilibrium = c("sum", "max"), mode = c("normal", "fast"), ...)
}

\arguments{
  \item{object}{an RHugin domain.}
  \item{equilibrium}{a character string specifying the equilibrium method.}
  \item{mode}{a character string specifying the evidence mode.}
  \item{\dots}{additional arguments are ignored.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_propagate}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("apple", echo = FALSE)

# Compile the domain
compile(apple)

# Select states
set.finding(apple, "Loses", "yes")

# Propagate and get beliefs
propagate(apple)
get.belief(apple, "Sick")
}

\keyword{programming}


