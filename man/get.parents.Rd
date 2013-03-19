\name{get.parents}
\alias{get.parents}

\title{Get Parents}

\description{
Return the names of the parent node(s) of \code{node}. For decision nodes, optionally return the requisite parents or the requisiste ancestors.
}

\usage{
get.parents(domain, node, type = "parents")
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string naming one node in \code{domain}.}
  \item{type}{either \code{"parents"}, \code{"requisite.parents"}, or \code{"requisiste.ancestors"}.}
}

\value{
a character vector containing the names of the parent nodes of \code{node}.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_get_parents}, \code{h_node_get_requisite_parents} and \code{h_node_get_requisite_ancestors}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("limid", echo = FALSE)
plot(limid)

get.parents(limid, "Sick1")
get.parents(limid, "Treat", type = "requisite.parents")
get.parents(limid, "Treat", type = "requisite.ancestors")
}

\keyword{programming}


