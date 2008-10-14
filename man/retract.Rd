\name{retract}
\alias{retract}

\title{Retract Evidence}

\description{
Retract evidence from one or more nodes in an RHugin domain.
}

\usage{
retract(domain, nodes)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{nodes}{an optional character vector specifying the names of the nodes for which evidence is to be retracted.}
}

\details{
The \code{nodes} argument is optional.  If only \code{domain} is given then evidence is retracted from all nodes.
}

\value{
a \code{NULL} value is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

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

# Retract evidence from Dry and propagate
retract(AppleTree, "Dry")
propagate(AppleTree)
get.belief(AppleTree, "Sick")

# Retract all evidence and propagate
retract(AppleTree)
propagate(AppleTree)
get.belief(AppleTree, "Sick")
}

\keyword{programming}


