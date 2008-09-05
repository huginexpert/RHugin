\name{simulate.RHuginDomain}
\alias{simulate.RHuginDomain}

\title{Simulate Cases}

\description{
Simulate cases with respect to the conditional distribution for the evidence.
}

\usage{
\method{simulate}{RHuginDomain}(object, nsim = 1, seed = NULL, ...)
}

\arguments{
  \item{object}{an RHugin domain object.}
  \item{nsim}{a single integer value specifying the number of cases to simulate.}
  \item{seed}{a single positive integer value used to seed Hugin's (NOT R's) random number generator.  If \code{NULL} then the current state for the random number generator is used.}
  \item{\dots}{any additional arguments are ignored.}
}

\value{
A data frame with one column for each node in the domain (\code{object}) whose rows contain the simulated cases.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{set.finding}},
  \code{\link{initialize.domain}}.
}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Select state
set.finding(AppleTree, "Loses", "yes")

# Propagate and get beliefs
propagate(AppleTree)

# Simulate cases
simulate(AppleTree, nsim = 5)
}

\keyword{programming}


