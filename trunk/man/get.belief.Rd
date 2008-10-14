\name{get.belief}
\alias{get.belief}

\title{Retrieving Beliefs}

\description{
Retrieve beliefs from a node after the domain has been compiled and evidence propagated.
}

\usage{
get.belief(domain, node, states = NULL)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character string specifying the name of the node from which the beliefs are to be retrieved.}
  \item{states}{an optional vector specifying the states of \sQuote{node} for which beliefs are to be retrieved.  If \code{NULL} then beliefs are retrieved for all states.}
}

\value{
a numeric vector containing the beliefs in the specified states.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Select state
set.finding(AppleTree, "Loses", "yes")

# Propagate and get beliefs
propagate(AppleTree)
get.belief(AppleTree, "Sick")
}

\keyword{programming}


