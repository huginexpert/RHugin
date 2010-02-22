\name{get.dconnected.nodes}
\alias{get.dconnected.nodes}
\alias{get.dseparated.nodes}

\title{Determining Independence Properties}

\description{
Compute the set of nodes either d-connected or d-separated from a given set of source nodes.
}

\usage{
get.dconnected.nodes(domain, source, hard, soft)
get.dseparated.nodes(domain, source, hard, soft)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{source}{a character vector containing the names of the source nodes.}
  \item{hard}{a character vector containing the names of the nodes for which hard evidence is entered.}
  \item{soft}{a character vector containing the names of the nodes for which soft evidence is entered.}
}

\value{
a character vector containing the names of the nodes that are either d-connected or d-separated.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_get_d_connected_nodes} and \code{h_domain_get_d_separated_nodes}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\keyword{programming}


