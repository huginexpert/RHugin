\name{get.normalization.constant}
\alias{get.normalization.constant}

\title{The Normalization Constant}

\description{
Get the normalization constant from an RHugin domain object.
}

\usage{
get.normalization.constant(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\value{
A single numeric value containing the normalization constant for the domain.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{compile}},
  \code{\link{set.finding}},
  \code{\link{propagate}},
  \code{\link{retract}}.
}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)

# Select state
set.finding(AppleTree, "Loses", "yes")

# Propagate and get beliefs
propagate(AppleTree)
get.normalization.constant(AppleTree)
}

\keyword{programming}


