\name{generate.table}
\alias{generate.table}

\title{Generate Table}

\description{
Generate a node's conditional probability table from its model.
}

\usage{
generate.table(domain, nodes)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{nodes}{a character vector specifying the names of the nodes in \code{domain} whose tables are to be generated.  If missing, tables for all nodes with models will be generated.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_generate_table} and \code{h_domain_generate_tables}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("asia", echo = FALSE)
}

\keyword{programming}


