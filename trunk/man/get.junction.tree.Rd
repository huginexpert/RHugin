\name{get.junction.tree}
\alias{get.junction.tree}

\title{Get Junction Tree(s)}

\description{
Retrieve the junction tree from a triangulated domain.
}

\usage{
get.junction.tree(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\value{
a list with one element for each junction tree in the triangulated domain.  Each element is in turn a list with the following elements:

  \item{cliques}{a list of the cliques making up the junction tree.  Each element is a character vector containing the names of the nodes in the clique.}

  \item{root}{a single integer value indicating which clique in \code{cliques} is the root of the junction tree.}

  \item{neighbors}{a list with one element for each clique.  Each element is a vector containing the indices (relative to \code{cliques}) of the neighboring cliques.}
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_get_first_junction_tree}, \code{h_jt_get_next}, \code{h_jt_get_root}, \code{h_jt_get_cliques}, \code{h_clique_get_members} and \code{h_clique_get_neighbors}.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\examples{
demo("apple", echo = FALSE)

# Triangulate the domain
triangulate(apple)

# Get junction tree
get.junction.tree(apple)
}

\keyword{programming}


