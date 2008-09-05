\name{set.finding}
\alias{set.finding}

\title{Set Finding}

\description{
Enter findings into a compiled RHugin domain object.
}

\usage{
set.finding(domain, node, finding)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character vector of length one giving the name of a node.}
  \item{finding}{a numeric vector containing the finding.  The length of \code{finding} must be equal to the number of states in \code{node} and all values must be nonnegative. Alternatively, \code{finding} may contain the name of a single state in \code{node}. In this case, the likelihood of that state is set to 1 and the likelihood for all other states is set to 0.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{retract}},
  \code{\link{get.finding}}.
}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Set finding
set.finding(AppleTree, "Loses", c(1, 0))

# Or equivalently
set.finding(AppleTree, "Loses", "yes")
}

\keyword{programming}


