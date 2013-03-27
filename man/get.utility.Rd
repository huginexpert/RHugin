\name{get.utility}
\alias{get.utility}

\title{Get Expected Utility}

\description{
Retrieve the expected utility for a node or a domain.
}

\usage{
get.utility(domain, node)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{an optional character string specifying the name of the node for which the expected utilities are to be retrieved.  If missing, the expected utility for the domain is returned.}
}

\value{
a numeric vector containing the expected utilities.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_get_expected_utility} and \code{h_domain_get_expected_utility}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\keyword{programming}


