\name{initialize.domain}
\alias{initialize.domain}

\title{Initialize a Domain}

\description{
Establish the initial values for all evidence, belief and junction tree tables in an RHugin domain.
}

\usage{
initialize.domain(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\details{
If an up-to-date memory backup exists (when \code{save = TRUE} in \code{\link{propagate}}) then the initialization is accomplished simply by loading the tables from the backup.  Otherwise, the initial values are recomputed from the conditional probability and utility potentials.  This function erases all previously entered evidence.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{set.finding}},
  \code{\link{retract}}.
}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Select states
set.finding(AppleTree, "Dry", "no")
set.finding(AppleTree, "Loses", "yes")

# Propagate and get beliefs
propagate(AppleTree)
get.belief(AppleTree, "Sick")

# Initialize the domain
initialize.domain(AppleTree)
}

\keyword{programming}

