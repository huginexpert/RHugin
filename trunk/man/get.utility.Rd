\name{get.utility}
\alias{get.utility}

\title{Retrieve Expected Utility}

\description{
Retrieve the expected utility from a node in an RHugin domain.
}

\usage{
get.utility(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of the node from which the expected utilities are to be retrieved.}
}

\value{
a numeric vector containing the expected utility for each state in \code{node}.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_node_get_expected_utility}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
}

\keyword{programming}


