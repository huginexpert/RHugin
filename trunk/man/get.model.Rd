\name{get.model}
\alias{get.model}

\title{Get Model}

\description{
Get the model for a node.
}

\usage{
get.model(domain, node, model.nodes)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{model.nodes}{an optional character vector of \emph{model nodes}. If provided, the model will have one expression for each configuration of the states of the model nodes.}
}

\details{
This function returns an R representation of the model for \code{node} (if \code{node} does not have a model, a new, empty model is created and returned).  If the R representation of the model is modified, it must be set using the \code{\link{set.model}} function before calling any function that could potentially generate tables (e.g., compilation). If not, the old model will be used.
}

\value{
a \code{data.frame}-like object with class \code{RHugin.model}. There is one column for each model node and a final column named \code{Expression} containing the expression for each configuration of the model nodes.  When there are no model nodes, the \code{Expression} column will have a single entry containing the model's expression.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_new_model} and \code{h_node_get_model}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("asia", echo = FALSE)
}

\keyword{programming}


