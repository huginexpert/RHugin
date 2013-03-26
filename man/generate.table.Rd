\name{generate.table}
\alias{generate.table}

\title{Generate Table}

\description{
Generate a conditional probability table from a node's model.
}

\usage{
generate.table(domain, nodes)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{nodes}{an optional character vector specifying the names of the nodes in \code{domain} whose tables are to be generated.  If missing, tables for all nodes with models will be generated.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_generate_table} and \code{h_domain_generate_tables}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
d <- hugin.domain()

# Add nodes
add.node(d, "Node", states = 0:10)

# Add a model
model <- get.model(d, "Node", character(0))
model$Expression <- "Poisson (2.25)"
set.model(d, "Node", model)

# Generate conditional probability table
generate.table(d, "Node")

get.table(d, "Node")
}

\keyword{programming}


