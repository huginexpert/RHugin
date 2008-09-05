\name{compile}
\alias{compile}

\title{Compile an RHugin Domain}

\description{
Compile an RHugin domain using the default triangulation method (unless the domain has already been triangulated).  The domain must contain at least one chance or decision node.
}

\usage{
compile(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{set.finding}},
  \code{\link{propagate}}.
}

\examples{
demo("buildAppleTreeNetwork")

# Compile the domain
compile(AppleTree)
}

\keyword{programming}


